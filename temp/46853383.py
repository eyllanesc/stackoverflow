from PyQt5 import QtWidgets, QtGui, QtCore


class ImageScroller(QtWidgets.QWidget):
    def __init__(self):
        self.chosen_points = []
        QtWidgets.QWidget.__init__(self)
        self._image = QtGui.QPixmap("/home/eyllanesc/face.png")

    def paintEvent(self, paint_event):
        painter = QtGui.QPainter(self)
        painter.drawPixmap(self.rect(), self._image)
        painter.setPen(QtGui.QPen(QtCore.Qt.red))
        pen = QtGui.QPen()
        pen.setWidth(20)
        painter.setPen(pen)
        painter.setRenderHint(QtGui.QPainter.Antialiasing, True)
        painter.drawPoint(300, 300)
        painter.drawLine(100, 100, 400, 400)
        for pos in self.chosen_points:
            painter.drawPoint(pos)

    def mouseReleaseEvent(self, cursor_event):
        self.chosen_points.append(cursor_event.pos())
        # self.chosen_points.append(self.mapFromGlobal(QtGui.QCursor.pos()))
        self.update()


if __name__ == '__main__':
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = ImageScroller()
    w.resize(640, 480)
    w.show()
    sys.exit(app.exec_())
