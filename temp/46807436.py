from PyQt4.QtCore import *
from PyQt4.QtGui import *


class Dial(QWidget):
    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        self.setPalette(QDial().palette())

    def paintEvent(self, event):
        r = min(self.rect().width(), self.rect().height())/2.25
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)
        p.setPen(Qt.NoPen)
        p.setBrush(self.palette().color(QPalette.Base))
        p.drawEllipse(self.rect().center(), r, r)

    def sizeHint(self):
        return QSize(96, 96)


class Widget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setLayout(QVBoxLayout())
        dial = Dial(self)
        label = QLabel(self)
        self.layout().addWidget(dial)
        self.layout().addWidget(label)
        # dial.valueChanged.connect(lambda val: label.setText("{}".format(val)))


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    app.setStyle("fusion")
    w = Widget()
    w.show()
    sys.exit(app.exec_())
