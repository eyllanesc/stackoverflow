import sys
from  PersonModel import PersonModel
from PyQt5.QtCore import QUrl
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from PyQt5.QtWidgets import QApplication

if __name__ == '__main__':
    myApp = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()
    engine.load(QUrl.fromLocalFile("main.qml"))
    if len(engine.rootObjects()) == 0:
        sys.exit(-1)
    sys.exit(myApp.exec_())
