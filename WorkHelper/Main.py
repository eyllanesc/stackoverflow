import sys
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from Main_GUI import *
from LoadInput_GUI import *


class LoadInput(QWidget):
	def __init__(self, parent=None):
		QWidget.__init__(self, parent)
		self.LoadInputGUI = Ui_LoadInput()
		self.LoadInputGUI.setupUi(self)


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        MainWindow = QtWidgets.QMainWindow()
        self.MainUi = Ui_MainWindow()
        self.MainUi.setupUi(self)

        self.setUpMainUiFunction()

    def setUpMainUiFunction(self):
        #Here is where all of the button functions will be definded
        self.MainUi.pushButton_2.clicked.connect(self.windowaction)

    def windowaction(self):
        sub = QtWidgets.QMdiSubWindow()
        Load_Input = LoadInput()
        sub.setWidget(Load_Input)
        sub.setObjectName("Load_Input_window")
        sub.setWindowTitle("Load Input")
        self.MainUi.mdiArea.addSubWindow(sub)
        sub.show()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = MainWindow()
    MainWindow.show()
    sys.exit(app.exec_())
