import os
from PyQt5 import QtCore, QtGui, QtWidgets

CURRENT_DIRECTORY = os.path.dirname(os.path.realpath(__file__))


def addText(pixmap, w, h, name):
    painter = QtGui.QPainter(pixmap)
    font = QtGui.QFont("Roboto")
    font.setPointSize(36)
    position = QtCore.QRect(0, 0, w, h)
    painter.setFont(font)
    painter.drawText(position, QtCore.Qt.AlignCenter, name)
    painter.end()
    return pixmap


def create_pixmap():
    pixmap = QtGui.QPixmap(512 * QtCore.QSize(1, 1))
    pixmap.fill(QtCore.Qt.white)
    return addText(pixmap, 512, 512, "Stack Overflow")


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    font_path = os.path.join(CURRENT_DIRECTORY, "Roboto", "Roboto-Regular.ttf")
    _id = QtGui.QFontDatabase.addApplicationFont(font_path)
    if QtGui.QFontDatabase.applicationFontFamilies(_id) == -1:
        print("problem loading font")
        sys.exit(-1)
    w = QtWidgets.QLabel()
    w.setPixmap(create_pixmap())
    w.show()
    sys.exit(app.exec_())
