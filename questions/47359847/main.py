import requests
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *

from WaitingSpinnerWidget import QtWaitingSpinner


class RequestRunnable(QRunnable):
    def __init__(self, url, json, dialog):
        QRunnable.__init__(self)
        self.mUrl = url
        self.mJson = json
        self.w = dialog

    def run(self):
        r = requests.post(self.mUrl, json=self.mJson)
        QThread.msleep(1000)
        QMetaObject.invokeMethod(self.w, "setData",
                                 Qt.QueuedConnection,
                                 Q_ARG(str, r.text))


class Dialog(QDialog):
    def __init__(self, *args, **kwargs):
        QDialog.__init__(self, *args, **kwargs)
        self.setLayout(QVBoxLayout())
        btn = QPushButton("Submit", self)
        btn.clicked.connect(self.submit)
        self.spinner = QtWaitingSpinner(self)

        self.layout().addWidget(btn)
        self.layout().addWidget(self.spinner)

    def submit(self):
        self.spinner.start()
        runnable = RequestRunnable("https://api.github.com/some/endpoint",
                                   {'some': 'data'},
                                   self)
        QThreadPool.globalInstance().start(runnable)

    @pyqtSlot(str)
    def setData(self, data):
        print(data)
        self.spinner.stop()
        self.adjustSize()


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    dial = Dialog()
    dial.show()
    sys.exit(app.exec_())
