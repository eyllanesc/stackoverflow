import sys
from PySide2 import QtCore, QtWidgets

from test_ui import Ui_MainWindow
from test_sub_ui import Ui_Form

# Variable which contains the subwindow ID
# Required to determine if a subwindow is already open
state_limitedSubWindow = None


class MyUI(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyUI, self).__init__(parent)
        self.setupUi(self)
        self.setWindowTitle("Test")
        self.mdiArea.addSubWindow(self.subwindow)
        self.actionOpenSubWindow.triggered.connect(self.func_limitedSubWindow)

    @QtCore.Slot()
    def printText(self):
        print("Debug: Inside the MainWindow class")
        self.printing()

    @QtCore.Slot()
    def func_limitedSubWindow(self):
        # loading global var which contains the subwindow ID
        global state_limitedSubWindow
        if state_limitedSubWindow == None:
            limitedSubWindow = LimitedSubWindow()
            self.mdiArea.addSubWindow(limitedSubWindow)
            limitedSubWindow.show()
            # Save ID of the new created subwindow in the global variable
            state_limitedSubWindow = limitedSubWindow.winId()
            # Console output subwindow ID
            print(state_limitedSubWindow)
        else:
            print("Window already exists !")
        pass

    @QtCore.Slot()
    def printing(self):
        self.textOutput.setPlainText("Test")


# Class for the limited second window (only 1 instance can be active)
# This class can of course be in a separate py file
# The base widget of the UI file must be QWidget !!!
class LimitedSubWindow(QtWidgets.QWidget, Ui_Form):
    def __init__(self, parent = None):
        super(LimitedSubWindow, self).__init__(parent)
        self.setupUi(self)
        self.setMinimumSize(400, 200)
        self.setWindowTitle("Limited subwindow")

    # Close event resets the variable which contains the ID
    def closeEvent(self, event):
        global state_limitedSubWindow
        # Reset the global variable
        state_limitedSubWindow = None
        event.accept()

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    # Creating an instance of the loading class
    frame = MyUI()
    frame.show()
    sys.exit(app.exec_())