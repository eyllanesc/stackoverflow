from PyQt5.QtCore import QUrl, QObject, pyqtSlot
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine


class Helper(QObject):
    @pyqtSlot(int)
    def fun(self, index):
        print(index)


if __name__ == '__main__':
    import sys

    app = QGuiApplication(sys.argv)

    engine = QQmlApplicationEngine()
    helper = Helper()
    engine.rootContext().setContextProperty("helper", helper)
    engine.load(QUrl.fromLocalFile("main.qml"))
    sys.exit(app.exec_())
