import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from doublespinbox import DoubleSpinBox


qtCreatorFile = "rvmod_gui.ui" # Enter file here.
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)


class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyApp, self).__init__(parent)
        self.setupUi(self)
        self.K1.minimize_signal.connect(self.on_minimize_k1)
    
    @QtCore.pyqtSlot()
    def on_minimize_k1(self):
        spinbox = self.sender()
        print(spinbox, "minimize k1")

def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main() 