from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtQml import *


class Runnable(QRunnable):
    def __init__(self, obj):
        QRunnable.__init__(self)
        # main thread
        self.obj = obj

    def run(self):
        # another thread
        self.obj.bar()


class Foo(QObject):
    def __init__(self, *args, **kwags):
        QObject.__init__(self, *args, **kwags)
        self._progress = 0

    @pyqtSlot()
    def run_bar(self):
        self.runnable = Runnable(self)
        QThreadPool.globalInstance().start(self.runnable)

    progressChanged = pyqtSignal(int)

    @pyqtProperty(int, notify=progressChanged)
    def progress(self):
        return self._progress


    @pyqtSlot(int)
    def updateProgress(self, value):
        if self._progress == value:
            return
        self._progress = value
        self.progressChanged.emit(self._progress)

    @pyqtSlot()
    def bar(self):
        for i in range(100):
            QMetaObject.invokeMethod(self, "updateProgress",
                                     Qt.QueuedConnection,
                                     Q_ARG(int, i))
            QThread.msleep(100)


if __name__ == '__main__':
    import sys

    app = QGuiApplication(sys.argv)
    qmlRegisterType(Foo, 'Foo', 1, 0, 'Foo')
    engine = QQmlApplicationEngine()
    engine.load(QUrl.fromLocalFile("main.qml"))
    if len(engine.rootObjects()) == 0:
        sys.exit(-1)
    sys.exit(app.exec_())
