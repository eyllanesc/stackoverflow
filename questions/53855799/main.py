from PyQt5 import QtCore, QtGui, QtWidgets

def addText(pixmap, w, h, name):
    painter = QtGui.QPainter(pixmap)        
    font = QtGui.QFont("Roboto")
    font.setPointSize(36)
    position  = QtCore.QRect(0, 0, w, h)
    painter.setFont(font);
    painter.drawText(position, QtCore.Qt.AlignCenter, name);
    painter.end()
    return pixmap

def create_pixmap():
	pixmap = QtGui.QPixmap(512*QtCore.QSize(1, 1))
	pixmap.fill(QtCore.Qt.white)
	return addText(pixmap, 512, 512, "Stack Overflow")

if __name__ == '__main__':
	import sys
	app = QtWidgets.QApplication(sys.argv)
	dir_ = QtCore.QDir("Roboto")
	_id = QtGui.QFontDatabase.addApplicationFont("Roboto/Roboto-Regular.ttf")
	print(QtGui.QFontDatabase.applicationFontFamilies(_id))
	w = QtWidgets.QLabel()
	w.setPixmap(create_pixmap())
	w.show()
	sys.exit(app.exec_())