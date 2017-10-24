from PyQt5.QtCore import *
from PyQt5.QtSql import *
from PyQt5.QtWidgets import *


def createConnection():
    db = QSqlDatabase.addDatabase("QSQLITE")
    db.setDatabaseName(QDir.current().filePath("data.db"))
    if not db.open():
        QMessageBox.critical(None, "Cannot open database",
                             "Unable to establish a database connection.\n"
                             "This example needs SQLite support. Please read "
                             "the Qt SQL driver documentation for information how "
                             "to build it.\n\n"
                             "Click Cancel to exit.",
                             QMessageBox.Cancel)
        return False

    query = QSqlQuery()
    query.exec("create table IF NOT EXISTS product(id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "date_and_time DATETIME, master VARCHAR(140), service VARCHAR(140), name VARCHAR(140),"
               "Contact_Number VARCHAR(140))")

    return True


class ClientDialog(QDialog):
    def __init__(self, *args, **kwargs):
        QDialog.__init__(self, *args, **kwargs)
        gridLayout = QGridLayout(self)
        self.masterCombo = QComboBox(self)
        self.serviceCombo = QComboBox(self)
        self.timeEdit = QDateTimeEdit(self)
        self.timeEdit.setDateTime(QDateTime.currentDateTime())
        self.timeEdit.setDisplayFormat("d/M/yy hh:mm")
        self.nameEdit = QLineEdit(self)
        self.contactNumberEdit = QLineEdit(self)
        self.cancelBtn = QPushButton("Cancel", self)
        self.acceptBtn = QPushButton("Add Client", self)
        self.cancelBtn.clicked.connect(self.reject)
        self.acceptBtn.clicked.connect(self.accept)

        gridLayout.addWidget(self.masterCombo, 0, 0)
        gridLayout.addWidget(self.serviceCombo, 0, 1)
        gridLayout.addWidget(QLabel("Date and Time", self), 1, 0, 1, 2)
        gridLayout.addWidget(self.timeEdit, 2, 0, 1, 2)
        gridLayout.addWidget(QLabel("Client Name", self), 3, 0)
        gridLayout.addWidget(QLabel("Contact Number", self), 3, 1)
        gridLayout.addWidget(self.nameEdit, 4, 0)
        gridLayout.addWidget(self.contactNumberEdit, 4, 1)
        gridLayout.addWidget(self.cancelBtn, 5, 0)
        gridLayout.addWidget(self.acceptBtn, 5, 1)
        self.setFixedSize(self.sizeHint())

    def data(self):
        master = self.masterCombo.currentText()
        service = self.serviceCombo.currentText()
        name = self.nameEdit.text()
        contact_number = self.contactNumberEdit.text()
        time = self.timeEdit.dateTime()
        return master, service, name, contact_number, time


class CustomProxyModel(QIdentityProxyModel):
    def __init__(self, c, *args, **kwargs):
        QIdentityProxyModel.__init__(self, *args, **kwargs)
        self.mapping = [None] * 25
        self.c = c

    def rowCount(self, parent=QModelIndex()):
        return 25

    def index(self, row, column, parent=QModelIndex()):
        return self.createIndex(row, column)

    def mapToSource(self, proxyIndex):
        if proxyIndex.isValid():
            r = self.mapping[proxyIndex.row()]
            if r is not None:
                return self.sourceModel().index(r, proxyIndex.column())
        return QModelIndex()

    def mapFromSource(self, sourceIndex):
        if sourceIndex.isValid():
            return self.createIndex(self.mapping.index(sourceIndex.row()), sourceIndex.column())
        return QModelIndex()

    def data(self, proxyIndex, role=Qt.DisplayRole):
        if not proxyIndex.isValid():
            return QVariant()

        val = QIdentityProxyModel.data(self, proxyIndex, role)
        if proxyIndex.column() == self.c:
            if role == Qt.DisplayRole:
                return QTime(8, 0).addSecs(30 * 60 * proxyIndex.row()).toString("h:mm")
        return val

    def flags(self, index):
        return QIdentityProxyModel.flags(self, index) | Qt.ItemIsEnabled

    def fixModel(self):
        self.layoutAboutToBeChanged.emit()
        self.mapping = [None] * 25
        for r in range(self.sourceModel().rowCount()):
            ix = self.sourceModel().index(r, self.c)
            data = self.sourceModel().data(ix)
            self.mapping[
                QTime(8, 0).secsTo(QDateTime.fromString(data.replace("T", " "), "yyyy-MM-dd hh:mm:ss.zzz").time()) // (
                    30 * 60)] = r
        self.layoutChanged.emit()
