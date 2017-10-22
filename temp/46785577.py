import sys
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtCore import *

from Ui_MainWindow import Ui_MainWindow


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(238, 260)
        self.tableWidget = QtWidgets.QTableWidget(Form)
        self.tableWidget.setGeometry(QtCore.QRect(10, 10, 221, 241))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(2)
        self.tableWidget.setRowCount(7)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(3, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(4, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(5, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(6, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setItem(0, 0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setItem(0, 1, item)

        # self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(281, 176)
        self.comboBox = QtWidgets.QComboBox(Dialog)
        self.comboBox.setGeometry(QtCore.QRect(90, 10, 71, 22))
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox_2 = QtWidgets.QComboBox(Dialog)
        self.comboBox_2.setGeometry(QtCore.QRect(10, 10, 71, 22))
        self.comboBox_2.setObjectName("comboBox_2")
        self.comboBox_2.addItem("")
        self.dateTimeEdit = QtWidgets.QDateTimeEdit(Dialog)
        self.dateTimeEdit.setGeometry(QtCore.QRect(10, 60, 194, 22))
        self.dateTimeEdit.setObjectName("dateTimeEdit")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(10, 40, 91, 16))
        self.label_2.setObjectName("label_2")
        self.lineEdit = QtWidgets.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(150, 110, 113, 20))
        self.lineEdit.setObjectName("lineEdit")
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(150, 90, 121, 16))
        self.label_3.setObjectName("label_3")
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(10, 110, 113, 20))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(10, 90, 111, 16))
        self.label_4.setObjectName("label_4")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(150, 140, 111, 23))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(10, 140, 111, 23))
        self.pushButton_2.setObjectName("pushButton_2")

        #    self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)


class Dialog(QtWidgets.QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        QtWidgets.QDialog.__init__(self, parent)
        self.setupUi(self)
        # cancel
        self.pushButton_2.clicked.connect(self.reject)
        # accept
        self.pushButton.clicked.connect(self.accept)
        self.dateTimeEdit.setDisplayFormat("d/M/yy hh:mm")


class Masters(QtWidgets.QDialog, Ui_Form):
    def __init__(self, parent=None):
        QtWidgets.QDialog.__init__(self, parent)
        self.setupUi(self)


class Table2ListProxyModel(QAbstractProxyModel):
    def __init__(self, parent=None):
        QAbstractProxyModel.__init__(self, parent)
        self.mapping = []

    def setSourceModel(self, sourceModel):
        sourceModel.dataChanged.connect(lambda: self.fixModel())
        QAbstractProxyModel.setSourceModel(self, sourceModel)
        self.fixModel()

    def mapFromSource(self, sourceIndex):
        if sourceIndex.isValid():
            key = self.mapping.index((sourceIndex.row(), sourceIndex.column()))
            return self.index(key, 0)
        return QModelIndex()

    def mapToSource(self, proxyIndex):
        if proxyIndex.isValid():
            r, c = self.mapping[proxyIndex.row()]
            return self.sourceModel().index(r, c)
        return QModelIndex()

    def rowCount(self, parent=QModelIndex()):
        return len(self.mapping)

    def columnCount(self, parent=QModelIndex()):
        return 1

    def index(self, row, column, parent=QModelIndex()):
        return self.createIndex(row, column)

    def parent(self, child):
        return QModelIndex()

    def fixModel(self):
        self.layoutAboutToBeChanged.emit()
        self.mapping = []
        for c in range(self.sourceModel().columnCount()):
            for r in range(self.sourceModel().rowCount()):
                ix = self.sourceModel().index(r, c)
                data = self.sourceModel().data(ix)
                if data is not None and data != "":
                    self.mapping.append((r, c))
        self.layoutChanged.emit()


"""class Services(QtWidgets.QDialog, Ui_SForm):
    def __init__(self, parent=None):
        QtWidgets.QDialog.__init__(self, parent)
        self.setupUi(self)"""


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        QtWidgets.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.addclient.clicked.connect(self.onAddClient)
        self.mastera.clicked.connect(self.AddMaster)
        self.masters = Masters(self)
        self.services = Services(self)
        self.dialog = Dialog(self)

        proxy = QSortFilterProxyModel()
        proxy.setSourceModel(self.masters.tableWidget.model())
        proxy.setFilterRegExp(".*\S.*")
        self.dialog.comboBox_2.setModel(proxy)

        proxy2 = QSortFilterProxyModel()
        proxy2.setFilterRegExp(".*\S.*")
        proxy2.setSourceModel(self.services.tableWidget.model())
        self.dialog.comboBox.setModel(proxy2)
        self.dialog.comboBox.setModelColumn(1)

    def AddService(self):
        self.services.show()

    def AddMaster(self):
        self.masters.show()

    def onAddClient(self):
        if self.dialog.exec_() == QtWidgets.QDialog.Accepted:
            master, service, name, contact_number, time = self.dialog.data()
            row = int(QtCore.QTime(8, 0).secsTo(time) / (30 * 60))
            if row >= 0:
                for k, text in enumerate([master, service, name, contact_number]):
                    self.tableWidget.setItem(row, k + 1, QtWidgets.QTableWidgetItem(text))


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
