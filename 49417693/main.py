import sys

from PyQt5.QtCore import QObject, QUrl, pyqtSlot
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine, QQmlComponent, QQmlContext

from SignalHandler import SignalHandler

if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    configurator = SignalHandler()

    engine.load("qml/SimpleMainWindow.qml")
    engine.quit.connect(app.quit)

    rootWindow = engine.rootObjects()[0]
    content_item = rootWindow.property("contentItem")

    context = QQmlContext(engine)
    component = QQmlComponent(engine)
    component.loadUrl(QUrl("qml/TestViewButton.qml"))
    itm = component.create(context)
    context.setContextProperty("configurator", configurator)
    itm.setProperty("parent", content_item)

    sys.exit(app.exec_())