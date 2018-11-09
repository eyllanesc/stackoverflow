import socketserver

import sys
from PyQt5 import QtWidgets, QtGui, QtCore
from time import sleep

import subprocess


class MyTCPHandler(socketserver.StreamRequestHandler):
    def handle(self):
        enabled = False
        a = 0
        while True:
            if not enabled:
                # self.rfile is a file-like object created by the handler;
                # we can now use e.g. readline() instead of raw recv() calls
                self.data = self.rfile.readline().strip()
                if a == 0:
                    print("{} wrote:".format(self.client_address[0]))
                    a += 1
                data = self.data.decode("utf-8").rstrip().strip("\n")
                if data != "":
                    if data == "disconnect":
                        print("restarting")
                        self.close()
                        sleep(1)
                    elif data == "shutdown":
                        p = subprocess.Popen("sudo shutdown -h now", shell=True, stdout=subprocess.PIPE,
                                             stderr=subprocess.STDOUT)
                        print(p)
                    else:
                        temp = data.split(":")
                        angle = int(temp[0])
                        strength = int(temp[1])
                        speed = float(temp[2])
                        QtCore.QMetaObject.invokeMethod(self.server.w, "setAngle",
                                                        QtCore.Qt.QueuedConnection,
                                                        QtCore.Q_ARG(int, angle))
                        QtCore.QMetaObject.invokeMethod(self.server.w, "setSpeed",
                                                        QtCore.Qt.QueuedConnection,
                                                        QtCore.Q_ARG(float, speed))


class ServerRunnable(QtCore.QRunnable):
    def __init__(self, w):
        QtCore.QRunnable.__init__(self)
        self.w = w

    def run(self):
        server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)
        server.w = self.w
        server.serve_forever()


class Ui_AppWindow(QtWidgets.QWidget):
    def __init__(self):
        super(Ui_AppWindow, self).__init__()
        self.setStyleSheet('background-color:#efefef; color:white;')
        self.layout = QtWidgets.QVBoxLayout()

        self.label = QtWidgets.QLabel("your_text")
        self.label.setStyleSheet("color: #005C99;")
        self.layout.addWidget(self.label)

        palette = QtGui.QPalette()
        palette.setColor(palette.WindowText, QtGui.QColor(85, 85, 255))
        palette.setColor(palette.Background, QtGui.QColor(0, 170, 255))
        palette.setColor(palette.Light, QtGui.QColor(0, 92, 153))
        palette.setColor(palette.Dark, QtGui.QColor(0, 92, 137))

        self.speed = QtWidgets.QLCDNumber(self)
        self.speed.setGeometry(QtCore.QRect(100, 100, 64, 23))
        self.speed.setObjectName("speed")

        self.speed.setPalette(palette)

        self.angle = QtWidgets.QLCDNumber(self)
        self.angle.setGeometry(QtCore.QRect(200, 100, 64, 23))
        self.angle.setObjectName("angle")
        self.angle.setPalette(palette)

        self.speed_lable = QtWidgets.QLabel("Speed")
        self.speed_lable.setGeometry(QtCore.QRect(100, 70, 47, 25))
        self.speed_lable.setObjectName("speed_lable")
        self.speed_lable.setStyleSheet('color:#00497a;')

        self.angle_lable = QtWidgets.QLabel("Angle")
        self.angle_lable.setGeometry(QtCore.QRect(200, 70, 47, 25))
        self.angle_lable.setObjectName("angle_lable")
        self.angle_lable.setStyleSheet('color:#00497a;')

        self.hbl = QtWidgets.QHBoxLayout()
        self.hbl.addWidget(self.speed_lable)
        self.hbl.addWidget(self.angle_lable)
        self.layout.addLayout(self.hbl)

        self.hb = QtWidgets.QHBoxLayout()
        self.hb.addWidget(self.speed)
        self.hb.addWidget(self.angle)
        self.layout.addLayout(self.hb)

        self.setWindowTitle("RasControl GUI: Android Control")
        self.setLayout(self.layout)
        self.setGeometry(100, 100, 400, 200)

    @QtCore.pyqtSlot(int)
    def setAngle(self, angle):
        self.angle.display(angle)

    @QtCore.pyqtSlot(float)
    def setSpeed(self, speed):
        self.speed.display(speed)


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    HOST, PORT = "localhost", 9000
    w = Ui_AppWindow()
    w.show()
    runnable = ServerRunnable(w)
    QtCore.QThreadPool.globalInstance().start(runnable)
    sys.exit(app.exec_())
