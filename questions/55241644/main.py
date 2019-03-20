from fakeuic import loadUiType  
from PySide2 import QtCore, QtGui, QtWidgets

Ui_FirstWindow, QFirstWindow = loadUiType('first_window.ui')
Ui_SecondWindow, QSecondWindow = loadUiType('second_window.ui')

class First(QFirstWindow, Ui_FirstWindow):
    def __init__(self):  
        super(First, self).__init__()
        self.setupUi(self)
        self.button.clicked.connect(self.show_second_window)

    def show_second_window(self):
        self.Second = Second()
        self.Second.show()

class Second(QSecondWindow, Ui_SecondWindow):
    def __init__(self):  
        super(Second, self).__init__()
        self.setupUi(self)

if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    main = First()
    main.show()
    sys.exit(app.exec_())