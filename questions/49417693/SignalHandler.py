from PyQt5.QtCore import QObject, pyqtSlot

class SignalHandler(QObject):

    @pyqtSlot(int, int)
    def sum(self, arg1, arg2):
        print("Adding two numbers")

    @pyqtSlot(str)
    def info(self, arg1):
        print("STR " + arg1)