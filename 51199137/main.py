from PyQt5.QtGui import QPainter, QPen, QColor
from PyQt5.QtSvg import QSvgRenderer
from PyQt5.QtCore import Qt, QRectF
from PyQt5.QtWidgets import QWidget, QApplication

class PyCounter(QWidget):
    def __init__(self, parent = None):
        super(PyCounter, self).__init__(parent)

        self.inicio()

    def getDigits(self):
        return self.m_digits

    def getValue(self):
        return self.m_value

    def getDigitsfile(self):
        return self.m_digitsFile

    def setValue(self, val):
        self.m_value = val
        self.update()

    def setDigits(self, dit):
        self.m_digits = dit
        self.update()

    def setDigitsFile(self, filemon):
        self.m_digitsFile = filemon
        if self.m_svg:
            del self.m_svg
        self.m_svg = QSvgRenderer(self)
        if not self.m_svg.load(self.m_digitsFile):
            print("Cannot load resource File")
            self.m_digitsFile = ":/default/resources/train_digits.svg"
            self.m_svg.load(self.m_digitsFile)
        else:
            print("Train digits correctly loaded")
        self.update()

    X_OFFSET = 10
    Y_OFFSET = 10

    def paintEvent(self, event):
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing, True)
        p.save()

        side = self.height()
        p.scale(side/100.0, side/100.0)
        width = 100 * self.width()
        height = 100 * self.height()


        width = 100.0 * self.width()/self.height() 
        height = 100.0

        pen = QPen(p.pen())

        pen.setColor(QColor(32,32,32))
        pen.setWidthF(6.0)
        p.setPen(pen)
        p.setBrush(Qt.black)
        p.drawRoundedRect(3,3,width-6,height-6,7,(7*width)/height)

        w = (width - 2*self.Y_OFFSET)/self.m_digits
        x = (self.m_digits-1) * w
        h = height-2*self.Y_OFFSET
        c = self.m_value
        r = 0

        for i in range(self.m_digits):
            r = c % 10
            c = c//10
            rect = QRectF(x + self.X_OFFSET, self.Y_OFFSET, w, h)
            self.m_svg.render(p, "d{}".format(r), rect)
            x -= w

        p.restore()

    def inicio(self):
        import analogwidgets_rc
        self.m_value = 0
        self.m_digits = 4
        self.m_svg = None
        self.setDigitsFile(":/default/resources/train_digits.svg")

if __name__ == '__main__':
    import sys
    from PyQt5.QtCore import QTimeLine

    app = QApplication(sys.argv)
    w = PyCounter()
    timeline = QTimeLine(10000)
    timeline.setFrameRange(0, 9999)
    timeline.frameChanged.connect(w.setValue)
    timeline.start()
    w.show()
    sys.exit(app.exec_())