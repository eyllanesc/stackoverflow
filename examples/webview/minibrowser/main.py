from PyQt5 import QtCore, QtGui, QtQml


class Utils(QtCore.QObject):
    @staticmethod
    @QtCore.pyqtSlot(str, result=QtCore.QUrl)
    def fromUserInput(userInput):
        if userInput:
            result = QtCore.QUrl.fromUserInput(userInput)
            return (
                result
                if result.isValid()
                else QtCore.QUrl.fromUserInput("about:blank")
            )
        else:
            return QtCore.QUrl.fromUserInput("about:blank")


import qml_rc


if __name__ == "__main__":
    import sys

    app = QtGui.QGuiApplication(sys.argv)
    QtGui.QGuiApplication.setApplicationDisplayName(
        QtCore.QCoreApplication.translate("main", "QtWebView Example")
    )

    parser = QtCore.QCommandLineParser()
    QtCore.QCoreApplication.setApplicationVersion(QtCore.QT_VERSION_STR)
    parser.setApplicationDescription(
        QtGui.QGuiApplication.applicationDisplayName()
    )
    parser.addHelpOption()
    parser.addVersionOption()
    parser.addPositionalArgument("url", "The initial URL to open.")
    arguments = app.arguments()
    parser.process(arguments)
    initialUrl = (
        parser.positionalArguments()[0]
        if parser.positionalArguments()
        else "https://www.qt.io"
    )

    engine = QtQml.QQmlApplicationEngine()
    context = engine.rootContext()
    context.setContextProperty("utils", Utils(engine))
    context.setContextProperty("initialUrl", Utils.fromUserInput(initialUrl))
    geometry = QtGui.QGuiApplication.primaryScreen().availableGeometry()
    if not QtGui.QGuiApplication.styleHints().showIsFullScreen():
        size = geometry.size() * 4 / 5
        offset = (geometry.size() - size) / 2
        pos = geometry.topLeft() - QtCore.QPoint(
            offset.width(), offset.height()
        )
        geometry = QtCore.QRect(pos, size)

    context.setContextProperty("initialX", geometry.x())
    context.setContextProperty("initialY", geometry.y())
    context.setContextProperty("initialWidth", geometry.width())
    context.setContextProperty("initialHeight", geometry.height())

    engine.load(QtCore.QUrl("qrc:/main.qml"))
    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec_())
