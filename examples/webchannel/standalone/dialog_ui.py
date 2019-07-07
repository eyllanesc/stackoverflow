# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/dialog.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(400, 300)
        self.gridLayout = QtWidgets.QGridLayout(Dialog)
        self.gridLayout.setObjectName("gridLayout")
        self.input = QtWidgets.QLineEdit(Dialog)
        self.input.setObjectName("input")
        self.gridLayout.addWidget(self.input, 1, 0, 1, 1)
        self.send = QtWidgets.QPushButton(Dialog)
        self.send.setObjectName("send")
        self.gridLayout.addWidget(self.send, 1, 1, 1, 1)
        self.output = QtWidgets.QPlainTextEdit(Dialog)
        self.output.setReadOnly(True)
        self.output.setPlainText("Initializing WebChannel...")
        self.output.setBackgroundVisible(False)
        self.output.setObjectName("output")
        self.gridLayout.addWidget(self.output, 0, 0, 1, 2)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.input.setPlaceholderText(_translate("Dialog", "Message Contents"))
        self.send.setText(_translate("Dialog", "Send"))




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
