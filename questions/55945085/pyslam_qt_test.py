import pyslam
from PyQt5 import QtCore, QtGui, QtWidgets


class Thread(QtCore.QThread):
    def run(self):
        obj = pyslam.Slam()
        obj.setParams(10)
        print("before")
        obj.start()
        print("after")


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = QtWidgets.QWidget()
    thread = Thread()
    QtCore.QTimer.singleShot(1000, thread.start)
    w.show()
    sys.exit(app.exec_())
