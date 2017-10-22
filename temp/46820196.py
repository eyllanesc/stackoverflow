from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class Drawer(QWidget):
    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        self.setFixedSize(self.size())
        self.point = QPoint()
        self.mPixmap = QPixmap(self.size())
        self.mPixmap.fill(Qt.green)
        self.modified = False

    def paintEvent(self, event):
        if self.modified:
            painter = QPainter(self.mPixmap)

            painter.setBrush(Qt.black)
            painter.drawEllipse(self.point, 2, 2)
            # painter.setPen(QPen(Qt.black, 4))
            # painter.drawPoint(self.point)
            self.modified = False
        painter = QPainter(self)
        painter.drawPixmap(0, 0, self.mPixmap)

    def mousePressEvent(self, event):
        self.point = event.pos()
        self.modified = True
        self.update()


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = Drawer()
    w.show()
    sys.exit(app.exec_())