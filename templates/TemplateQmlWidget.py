from PyQt5 import QtCore, QtGui, QtQml

if __name__ == '__main__':
    import os
    import sys
    # sys.argv += ['--style', 'material']
    app = QtGui.QGuiApplication(sys.argv)
    engine = QtQml.QQmlApplicationEngine()
    # engine.rootContext().setContextProperty()
    file = os.path.join(os.path.dirname(
        os.path.realpath(__file__)), "main.qml")
    engine.load(QtCore.QUrl.fromLocalFile(file))
    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec())
