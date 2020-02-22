import configparser
from PyQt5 import QtCore, QtGui, QtWidgets

from main_ui import Ui_MainWindow
from autobowgui import AutoBowGui


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.AutoBowO.clicked.connect(self.AutoBowOptions)

    def AutoBowOptions(self):
    	d = AutoBowGui()
    	self.hide()
    	d.exec_()
    	self.show()
        


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
