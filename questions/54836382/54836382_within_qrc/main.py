import os
import sys
from PyQt5 import QtCore, QtGui, QtQml

import qml_rc

if __name__ == '__main__':
	os.environ["QT_AUTO_SCREEN_SCALE_FACTOR"] = "1" 
	app = QtGui.QGuiApplication(sys.argv)
	app.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
	#Initialize the QML rendering engine
	engine = QtQml.QQmlApplicationEngine()
	#Load the main window element
	ctx = engine.rootContext()
	engine.load(QtCore.QUrl("qrc:/qml/main.qml"))
	#Show the Application Window
	if not engine.rootObjects():
		sys.exit(-1)
	#Execute and cleanup
	sys.exit(app.exec_())