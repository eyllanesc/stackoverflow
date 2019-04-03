# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'test.ui',
# licensing of 'test.ui' applies.
#
# Created: Wed Apr  3 18:30:03 2019
#      by: pyside2-uic  running on PySide2 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PySide2 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.horizontalLayoutWidget.setGeometry(QtCore.QRect(0, 0, 791, 551))
        self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.textInput = QtWidgets.QPlainTextEdit(self.horizontalLayoutWidget)
        self.textInput.setObjectName("textInput")
        self.horizontalLayout.addWidget(self.textInput)
        self.mdiArea = QtWidgets.QMdiArea(self.horizontalLayoutWidget)
        self.mdiArea.setEnabled(True)
        self.mdiArea.setMaximumSize(QtCore.QSize(517, 16777215))
        self.mdiArea.setObjectName("mdiArea")
        self.subwindow = QtWidgets.QWidget()
        self.subwindow.setMinimumSize(QtCore.QSize(400, 400))
        self.subwindow.setObjectName("subwindow")
        self.pushButton = QtWidgets.QPushButton(self.subwindow)
        self.pushButton.setGeometry(QtCore.QRect(160, 200, 90, 28))
        self.pushButton.setObjectName("pushButton")
        self.horizontalLayout.addWidget(self.mdiArea)
        self.textOutput = QtWidgets.QPlainTextEdit(self.horizontalLayoutWidget)
        self.textOutput.setObjectName("textOutput")
        self.horizontalLayout.addWidget(self.textOutput)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 23))
        self.menubar.setObjectName("menubar")
        self.menuWorkbench = QtWidgets.QMenu(self.menubar)
        self.menuWorkbench.setObjectName("menuWorkbench")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionOpenSubWindow = QtWidgets.QAction(MainWindow)
        self.actionOpenSubWindow.setObjectName("actionOpenSubWindow")
        self.actionTestText = QtWidgets.QAction(MainWindow)
        self.actionTestText.setObjectName("actionTestText")
        self.menuWorkbench.addAction(self.actionOpenSubWindow)
        self.menubar.addAction(self.menuWorkbench.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QObject.connect(self.pushButton, QtCore.SIGNAL("clicked()"), MainWindow.printText)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtWidgets.QApplication.translate("MainWindow", "MainWindow", None, -1))
        self.subwindow.setWindowTitle(QtWidgets.QApplication.translate("MainWindow", "Subwindow", None, -1))
        self.pushButton.setText(QtWidgets.QApplication.translate("MainWindow", "PushButton", None, -1))
        self.menuWorkbench.setTitle(QtWidgets.QApplication.translate("MainWindow", "Workbench", None, -1))
        self.actionOpenSubWindow.setText(QtWidgets.QApplication.translate("MainWindow", "Caesar Cipher", None, -1))
        self.actionTestText.setText(QtWidgets.QApplication.translate("MainWindow", "Test text", None, -1))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

