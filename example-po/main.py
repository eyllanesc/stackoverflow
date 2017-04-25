from PyQt4 import QtCore, QtGui
import sys
import gettext

#Utf-8 Encoding generated from Qt Designer
try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)


class MainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__()
        #Calling the Slides Widget class and the MainWindow setup
        self.setupUi(self)

    def setupUi(self, MainWindow):
        MainWindow.resize(1269, 688)

        self.label_4 = QtGui.QLabel(self)
        self.label_4.setGeometry(QtCore.QRect(110, 30, 191, 21))
        font = QtGui.QFont()
        font.setFamily(_fromUtf8("Lucida Sans"))
        font.setPointSize(12)
        font.setBold(False)
        font.setWeight(50)
        self.label_4.setFont(font)

        self.pushButton_EN = QtGui.QPushButton(self)
        self.pushButton_EN.setGeometry(QtCore.QRect(1000, 30, 75, 23))
       	self.pushButton_EN.clicked.connect(lambda: self.enTranslate(MainWindow))
        self.pushButton_IE = QtGui.QPushButton(self)
        self.pushButton_IE.setGeometry(QtCore.QRect(1100, 30, 75, 23))
        self.pushButton_IE.clicked.connect(lambda: self.ieTranslate(MainWindow))
        self.enTranslate(MainWindow)

    def enTranslate(self, MainWindow):
    	self.translate('en', MainWindow)

    def ieTranslate(self, MainWindow):
    	self.translate('ie', MainWindow)

    def translate(self, lang, MainWindow):
    	self.messages = gettext.translation('messages', localedir='locale', languages=[lang])
    	self.messages.install()
    	self.retranslateUi(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Erasmus", None))
        self.pushButton_EN.setText(_translate("MainWindow", _("English"), None))
        self.pushButton_IE.setText(_translate("MainWindow", _("Irish"), None))
        self.label_4.setText(_translate("MainWindow", _("Don\'t have an account?"), None))


if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	Win = MainWindow()
	Win.show()
	sys.exit(app.exec_())