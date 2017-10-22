from PyQt5.QtCore import *
from PyQt5.QtSerialPort import *


class Scanner(QObject):
    finished = pyqtSignal()
    newPort = pyqtSignal(str)

    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self.stopped = False

    def doScan(self):
        for portInfo in QSerialPortInfo.availablePorts():
            if portInfo.isValid() and not portInfo.isBusy():
                if self.isPayloadValid(portInfo):
                    print(portInfo.portName())
                    self.newPort.emit(portInfo.portName())
            QThread.msleep(10)
        self.finished.emit()

    def isPayloadValid(self, info):
        serial = QSerialPort(info)
        serial.setBaudRate(QSerialPort.Baud9600)
        if serial.open(QSerialPort.ReadOnly):
            while serial.waitForReadyRead(100):
                QThread.currentThread().msleep(10)
            if bytearray(serial.read(1)).decode() == "*":
                return True
        return False


class Listener(QObject):
    def __init__(self, portName, parent=None):
        QObject.__init__(self, parent)
        self.serial = QSerialPort(portName)
        self.serial.setBaudRate(QSerialPort.Baud9600)
        self.serial.readyRead.connect(self.onReadyRead)
        self.serial.error.connect(self.handleError)

    def onReadyRead(self):
        print("read", self.serial.readAll())

    def handleError(self, error):
        print("error", error)

    def start(self):
        print(self.serial.open(QSerialPort.ReadWrite))


class Manager(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self.scanner = Scanner(self)
        self.thread = QThread(self)
        self.thread.started.connect(self.scanner.doScan)
        self.scanner.finished.connect(self.thread.quit)
        # self.scanner.finished.connect(self.thread.deleteLater)
        self.thread.finished.connect(self.scanner.deleteLater)
        self.scanner.newPort.connect(self.onNewPort)
        self.thread.start()
        self.listeners = []

    def onNewPort(self, portName):
        listener = Listener(portName, self)
        listener.start()


if __name__ == '__main__':
    import sys

    app = QCoreApplication(sys.argv)
    thread = Manager()
    sys.exit(app.exec_())
