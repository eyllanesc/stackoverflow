from PyQt5.QtCore import Qt
from PyQt5.QtGui import QBrush
from PyQt5.QtSql import QSqlQuery, QSqlQueryModel, QSqlDatabase
from PyQt5.QtWidgets import QTableView, QApplication, QMessageBox, qApp


def createConnection():
    db = QSqlDatabase.addDatabase('QSQLITE')
    db.setDatabaseName('memory')
    if not db.open():
        QMessageBox.critical(None, qApp.tr("Cannot open database"),
                             qApp.tr("Unable to establish a database connection.\n"
                                     "This example needs SQLite support. Please read "
                                     "the Qt SQL driver documentation for information "
                                     "how to build it.\n\n"
                                     "Click Cancel to exit."),
                             QMessageBox.Cancel)
        return False

    query = QSqlQuery()
    query.exec_("create table person(id int primary key, "
                "firstname varchar(20), lastname varchar(20),"
                "archive BOOLEAN NOT NULL CHECK (archive IN (0,1)))")

    query.exec_("insert into person values(101, 'Danny', 'Young', 1)")
    query.exec_("insert into person values(102, 'Christine', 'Holand', 0)")
    query.exec_("insert into person values(103, 'Lars', 'Gordon', 1)")
    query.exec_("insert into person values(104, 'Roberto', 'Robitaille', 0)")
    query.exec_("insert into person values(105, 'Maria', 'Papadopoulos', 1)")
    query.exec_("insert into person values(106, 'Luisa', 'Papadopoulos', 1)")
    query.exec_("insert into person values(107, 'Luis', 'Papadopoulos', 1)")

    return True


class CustomSqlModel(QSqlQueryModel):
    def __init__(self, parent=None):
        QSqlQueryModel.__init__(self, parent=parent)
        self.setQuery("select * from person")

    def data(self, item, role):
        if role == Qt.BackgroundRole:
            if QSqlQueryModel.data(self, self.index(item.row(), 3), Qt.DisplayRole):
                return QBrush(Qt.yellow)
        if role == Qt.DisplayRole:
            if item.column() == 3:
                return True if QSqlQueryModel.data(self, item, Qt.DisplayRole) == 1 else False
        return QSqlQueryModel.data(self, item, role)

if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)

    if not createConnection():
        sys.exit(1)

    model = CustomSqlModel()

    view = QTableView()
    view.resizeColumnsToContents()
    view.setModel(model)
    view.setWindowTitle("Custom Model")

    view.show()

    sys.exit(app.exec_())
