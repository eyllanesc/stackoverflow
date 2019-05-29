from PyQt5 import QtCore, QtGui, QtWidgets

from stylewidget_ui import Ui_StyleWidget


class StyleWidget(QtWidgets.QFrame):
    def __init__(self, parent=None):
        super(StyleWidget, self).__init__(parent)
        self.ui = Ui_StyleWidget()
        self.ui.setupUi(self)

    @QtCore.pyqtSlot()
    def on_close_clicked(self):
    	self.close()

    @QtCore.pyqtSlot()
    def on_blueStyle_clicked(self):
        styleSheet = QtCore.QFile(":/files/blue.qss")
        if not styleSheet.open(QtCore.QIODevice.ReadOnly):
            print("Unable to open :/files/blue.qss")
            return
        QtWidgets.qApp.setStyleSheet(styleSheet.readAll().data().decode())

    @QtCore.pyqtSlot()
    def on_khakiStyle_clicked(self):
        styleSheet = QtCore.QFile(":/files/khaki.qss")
        if not styleSheet.open(QtCore.QIODevice.ReadOnly):
            print("Unable to open :/files/khaki.qss")
            return
        QtWidgets.qApp.setStyleSheet(styleSheet.readAll().data().decode())

    @QtCore.pyqtSlot()
    def on_noStyle_clicked(self):
        styleSheet = QtCore.QFile(":/files/nostyle.qss")
        if not styleSheet.open(QtCore.QIODevice.ReadOnly):
            print("Unable to open :/files/nostyle.qss")
            return
        QtWidgets.qApp.setStyleSheet(styleSheet.readAll().data().decode())

    @QtCore.pyqtSlot()
    def on_transparentStyle_clicked(self):
        styleSheet = QtCore.QFile(":/files/transparent.qss")
        if not styleSheet.open(QtCore.QIODevice.ReadOnly):
            print("Unable to open :/files/transparent.qss")
            return
        QtWidgets.qApp.setStyleSheet(styleSheet.readAll().data().decode())


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = StyleWidget()
    w.show()
    sys.exit(app.exec_())
