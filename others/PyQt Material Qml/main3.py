import os
import sys
from PyQt5 import QtCore, QtGui, QtQml

if __name__ == '__main__':
	app = QtGui.QGuiApplication(sys.argv)
	os.environ["QT_QUICK_CONTROLS_STYLE"] = "Material"
	engine = QtQml.QQmlApplicationEngine()
	dir_path = os.path.dirname(os.path.realpath(__file__))
	engine.load(QtCore.QUrl.fromLocalFile(os.path.join(dir_path, 'main.qml')))
	if not engine.rootObjects():
		sys.exit(-1)
	sys.exit(app.exec_())