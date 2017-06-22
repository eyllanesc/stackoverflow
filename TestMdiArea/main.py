import sys

# import Logo_rc
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QMainWindow, QMdiSubWindow

from HomeWindow import Ui_HomeWindow
from MainWindow import Ui_MainWindow
from ValveSim import Ui_ValveSim


class HomeWindow(QMainWindow, Ui_HomeWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setupUi(self)


class ValveSim(QMainWindow, Ui_ValveSim):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setupUi(self)


class Win1(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setupUi(self)
        self.vs = ValveSim()
        self.CreateValveSimulator()
        self.CreateWindow()

    def CreateValveSimulator(self):
        self.subwindow = QMdiSubWindow()
        self.subwindow.setWidget(self.vs)
        self.mdiArea.addSubWindow(self.subwindow)
        self.subwindow.setFixedSize(500, 500)
        # self.subwindow.close()

    def CreateWindow(self):
        w = HomeWindow()
        w.pushButton.clicked.connect(self.vs.show)
        self.subwindow = QMdiSubWindow()
        self.subwindow.setWindowFlags(Qt.CustomizeWindowHint | Qt.Tool)
        self.subwindow.setWidget(w)
        self.mdiArea.addSubWindow(self.subwindow)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = Win1()
    win.show()
    sys.exit(app.exec_())
