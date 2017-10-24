from PyQt5.QtCore import *
from PyQt5.QtSql import *
from PyQt5.QtWidgets import *

from util import ClientDialog, createConnection, CustomProxyModel


class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.centralWidget = QWidget(self)
        self.setCentralWidget(self.centralWidget)
        hlayout = QHBoxLayout(self.centralWidget)
        vlayout = QVBoxLayout()
        self.calendarWidget = QCalendarWidget(self.centralWidget)
        self.calendarWidget.setSizePolicy(QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed))
        self.masterBtn = QPushButton("Master", self.centralWidget)
        self.serviceBtn = QPushButton("Service", self.centralWidget)
        self.clientBtn = QPushButton("Client", self.centralWidget)
        spacerItem = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        vlayout.addWidget(self.calendarWidget)
        vlayout.addWidget(self.masterBtn)
        vlayout.addWidget(self.serviceBtn)
        vlayout.addWidget(self.clientBtn)
        vlayout.addItem(spacerItem)

        hlayout.addLayout(vlayout)
        self.view = QTableView(self.centralWidget)
        hlayout.addWidget(self.view)

        self.model = QSqlTableModel()
        self.model.setTable("product")
        self.proxy = CustomProxyModel(1)
        self.proxy.setSourceModel(self.model)

        self.view.setModel(self.proxy)
        self.view.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.view.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeToContents)
        self.view.hideColumn(0)
        self.model.setHeaderData(1, Qt.Horizontal, "Time")
        self.model.setHeaderData(5, Qt.Horizontal, "Contact Number")

        self.clientBtn.clicked.connect(self.onAddClient)
        self.calendarWidget.clicked.connect(self.onSelectDay)
        self.onSelectDay(self.calendarWidget.selectedDate())

    def onAddClient(self):
        client = ClientDialog(self)
        proxy = QSortFilterProxyModel()
        proxy.setSourceModel(self.view.model())
        proxy.setFilterRegExp(".*\S.*")
        client.masterCombo.setModel(proxy)
        client.masterCombo.setModelColumn(2)
        client.serviceCombo.setModel(proxy)
        client.serviceCombo.setModelColumn(3)

        if client.exec_() == ClientDialog.Accepted:
            master, service, name, contact_number, datetime = client.data()
            time = datetime.time()
            if QTime(8, 0) > time or QTime(20, 0) < time:
                return
            datetime = QDateTime(datetime.date(), QTime(8, 0).addSecs(30*60*int(QTime(8, 0).secsTo(time)/(30*60))))
            query = QSqlQuery()
            query.prepare("SELECT * FROM product WHERE date_and_time=:date_and_time")
            query.bindValue(":date_and_time", datetime)
            query.exec_()
            if query.next():
                id = query.value(0)
                query.prepare("UPDATE product SET master= :master, service=:service, name=:name, "
                              "Contact_Number=:contact_number where id = :id")
                query.bindValue(":id", id)
            else:
                query.prepare("INSERT INTO product(date_and_time, master, service, name, Contact_Number)"
                              "VALUES (:date_and_time, :master, :service, :name, :contact_number)")
                query.bindValue(":date_and_time", datetime)
            query.bindValue(":master", master)
            query.bindValue(":service", service)
            query.bindValue(":name", name)
            query.bindValue(":contact_number", contact_number)
            if not query.exec_():
                query.lastError().text()
            self.onSelectDay(self.calendarWidget.selectedDate())

    def onSelectDay(self, date):
        start = QDateTime(date)
        stop = start.addDays(1)
        self.model.setFilter("date_and_time BETWEEN DATETIME('{}') AND DATETIME('{}')".
                             format(start.toString("yyyy-MM-dd hh:mm:ss.zzz"),
                                    stop.toString("yyyy-MM-dd hh:mm:ss.zzz")))
        self.model.select()
        self.proxy.fixModel()


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    app.setStyle("fusion")
    if not createConnection():
        sys.exit(-1)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
