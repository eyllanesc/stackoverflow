from enum import IntEnum

from PyQt5 import QtCore, QtGui, QtWidgets


class Transition(IntEnum):
    Slide, Flip, Rotate = range(3)


class Digits(QtWidgets.QWidget):

    QtCore.Q_ENUM(Transition)

    def __init__(self, parent=None):
        super(Digits, self).__init__(parent)
        self.m_number = 0
        self.m_transition = Transition.Slide
        self.m_pixmap = QtGui.QPixmap()
        self.m_lastPixmap = QtGui.QPixmap()

        self.setAttribute(QtCore.Qt.WA_OpaquePaintEvent, True)
        self.setAttribute(QtCore.Qt.WA_NoSystemBackground, True)
        self.m_animator = QtCore.QTimeLine(
            frameChanged=self.update, duration=600
        )
        self.m_animator.setCurveShape(QtCore.QTimeLine.EaseInOutCurve)
        self.m_animator.setFrameRange(0, 100)

    def setTransition(self, tr):
        self.m_transition = tr

    def transition(self):
        return self.m_transition

    def setNumber(self, n):
        if self.m_number != n:
            self.m_number = min(max(0, n), 99)
            self.preparePixmap()
            self.update()

    def flipTo(self, n):
        if self.m_number != n:
            self.m_number = min(max(0, n), 99)
            self.preparePixmap()
            self.m_animator.stop()
            self.m_animator.start()

    def drawFrame(self, painter, rect):
        painter.setPen(QtCore.Qt.NoPen)
        gradient = QtGui.QLinearGradient(rect.topLeft(), rect.bottomLeft())
        gradient.setColorAt(0.00, QtGui.QColor(245, 245, 245))
        gradient.setColorAt(0.49, QtGui.QColor(192, 192, 192))
        gradient.setColorAt(0.51, QtGui.QColor(245, 245, 245))
        gradient.setColorAt(1.00, QtGui.QColor(192, 192, 192))
        painter.setBrush(gradient)
        r = QtCore.QRect(rect)
        painter.drawRoundedRect(r, 15, 15, QtCore.Qt.RelativeSize)
        r.adjust(1, 4, -1, -4)
        painter.setPen(QtGui.QColor(181, 181, 181))
        painter.setBrush(QtCore.Qt.NoBrush)
        painter.drawRoundedRect(r, 15, 15, QtCore.Qt.RelativeSize)
        painter.setPen(QtGui.QColor(159, 159, 159))
        y = rect.top() + rect.height() / 2 - 1
        painter.drawLine(rect.left(), y, rect.right(), y)

    def drawDigits(self, n, rect):
        scaleFactor = 2

        n_str = str(n)
        if len(n_str) == 1:
            n_str = "0" + n_str

        font = QtGui.QFont()
        font.setFamily("Helvetica")
        fontHeight = scaleFactor * 0.55 * rect.height()
        font.setPixelSize(fontHeight)
        font.setBold(True)

        pixmap = QtGui.QPixmap(rect.size() * scaleFactor)
        pixmap.fill(QtCore.Qt.transparent)

        gradient = QtGui.QLinearGradient(
            QtCore.QPoint(0, 0), QtCore.QPoint(0, pixmap.height())
        )
        gradient.setColorAt(0.00, QtGui.QColor(128, 128, 128))
        gradient.setColorAt(0.49, QtGui.QColor(64, 64, 64))
        gradient.setColorAt(0.51, QtGui.QColor(128, 128, 128))
        gradient.setColorAt(1.00, QtGui.QColor(16, 16, 16))

        painter = QtGui.QPainter(pixmap)
        painter.setFont(font)
        pen = QtGui.QPen()
        pen.setBrush(QtGui.QBrush(gradient))
        painter.setPen(pen)
        painter.drawText(pixmap.rect(), QtCore.Qt.AlignCenter, n_str)
        painter.end()

        return pixmap.scaledToWidth(
            self.width(), QtCore.Qt.SmoothTransformation
        )

    def preparePixmap(self):
        self.m_pixmap = QtGui.QPixmap(self.size())
        self.m_pixmap.fill(QtCore.Qt.transparent)
        painter = QtGui.QPainter(self.m_pixmap)
        painter.drawPixmap(0, 0, self.drawDigits(self.m_number, self.rect()))
        painter.end()

    def resizeEvent(self, event):
        self.preparePixmap()
        self.update()

    def paintStatic(self):
        painter = QtGui.QPainter(self)
        painter.fillRect(self.rect(), QtCore.Qt.black)

        pad = self.width() / 10
        self.drawFrame(painter, self.rect().adjusted(pad, pad, -pad, -pad))
        painter.drawPixmap(0, 0, self.m_pixmap)

    def paintSlide(self):
        painter = QtGui.QPainter(self)
        painter.fillRect(self.rect(), QtCore.Qt.black)

        pad = self.width() / 10
        fr = self.rect().adjusted(pad, pad, -pad, -pad)
        self.drawFrame(painter, fr)
        painter.setClipRect(fr)

        y = self.height() * self.m_animator.currentFrame() / 100
        painter.drawPixmap(0, y, self.m_lastPixmap)
        painter.drawPixmap(0, y - self.height(), self.m_pixmap)

    def paintFlip(self):
        painter = QtGui.QPainter(self)
        painter.setRenderHint(QtGui.QPainter.SmoothPixmapTransform, True)
        painter.setRenderHint(QtGui.QPainter.Antialiasing, True)
        painter.fillRect(self.rect(), QtCore.Qt.black)

        hw = self.width() / 2
        hh = self.height() / 2

        pad = self.width() / 10
        fr = self.rect().adjusted(pad, pad, -pad, -pad)
        self.drawFrame(painter, fr)
        painter.drawPixmap(0, 0, self.m_pixmap)

        index = self.m_animator.currentFrame()

        if index <= 50:
            angle = -180 * index / 100
            transform = QtGui.QTransform()
            transform.translate(hw, hh)
            transform.rotate(angle, QtCore.Qt.XAxis)
            painter.setTransform(transform)
            painter.drawPixmap(-hw, -hh, self.m_lastPixmap)

            painter.resetTransform()
            painter.setClipRect(0, hh, self.width(), hh)
            self.drawFrame(painter, fr)
            painter.drawPixmap(0, 0, self.m_lastPixmap)
        else:
            painter.setClipRect(0, hh, self.width(), hh)

            self.drawFrame(painter, fr)
            painter.drawPixmap(0, 0, self.m_lastPixmap)

            angle = 180 - 180 * self.m_animator.currentFrame() / 100
            transform = QtGui.QTransform()
            transform.translate(hw, hh)
            transform.rotate(angle, QtCore.Qt.XAxis)
            painter.setTransform(transform)
            self.drawFrame(painter, fr.adjusted(-hw, -hh, -hw, -hh))
            painter.drawPixmap(-hw, -hh, self.m_pixmap)

    def paintRotate(self):
        painter = QtGui.QPainter(self)

        pad = self.width() / 10
        fr = self.rect().adjusted(pad, pad, -pad, -pad)
        self.drawFrame(painter, fr)
        painter.setClipRect(fr)

        angle1 = -180 * self.m_animator.currentFrame() / 100
        angle2 = 180 * self.m_animator.currentFrame() / 100
        angle = angle1 if self.m_animator.currentFrame() <= 50 else angle2
        pix = (
            self.m_lastPixmap
            if self.m_animator.currentFrame() <= 50
            else self.m_pixmap
        )

        transform = QtGui.QTransform()
        transform.translate(self.width() / 2, self.height() / 2)
        transform.rotate(angle, QtCore.Qt.XAxis)

        painter.setTransform(transform)
        painter.setRenderHint(QtGui.QPainter.SmoothPixmapTransform, True)
        painter.drawPixmap(-self.width() / 2, -self.height() / 2, pix)

    def paintEvent(self, event):

        if self.m_animator.state() == QtCore.QTimeLine.Running:
            if self.m_transition == Transition.Slide:
                self.paintSlide()
            elif self.m_transition == Transition.Flip:
                self.paintFlip()
            elif self.m_transition == Transition.Rotate:
                self.paintRotate()
        else:
            self.paintStatic()


class DigiFlip(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super(DigiFlip, self).__init__(parent)

        self.m_ticker = QtCore.QBasicTimer()

        self.m_hour = Digits(self)
        self.m_hour.show()
        self.m_minute = Digits(self)
        self.m_minute.show()

        pal = QtGui.QPalette(self.palette())
        pal.setColor(QtGui.QPalette.Window, QtCore.Qt.black)
        self.setPalette(pal)

        self.m_ticker.start(1000, self)
        t = QtCore.QTime.currentTime()
        self.m_hour.setNumber(t.hour())
        self.m_minute.setNumber(t.minute())
        self.updateTime()

        slideAction = QtWidgets.QAction("&Slide", triggered=self.chooseSlide)
        flipAction = QtWidgets.QAction("&Flip", self, triggered=self.chooseFlip)
        rotateAction = QtWidgets.QAction(
            "&Rotate", self, triggered=self.chooseRotate
        )
        for action in (slideAction, flipAction, rotateAction):
            self.addAction(action)
        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

    def updateTime(self):
        t = QtCore.QTime.currentTime()
        self.m_hour.flipTo(t.hour())
        self.m_minute.flipTo(t.minute())
        t_str = t.toString("hh:mm:ss")
        t_str = ": " + t_str
        if self.m_hour.transition() == Transition.Slide:
            t_str = "Slide" + t_str
        elif self.m_hour.transition() == Transition.Flip:
            t_str = "Flip" + t_str
        elif self.m_hour.transition() == Transition.Rotate:
            t_str = "Rotate" + t_str
        self.setWindowTitle(t_str)

    def switchTransition(self, delta):
        i = (self.m_hour.transition() + delta + 3) % 3
        self.m_hour.setTransition(i)
        self.m_minute.setTransition(i)
        self.updateTime()

    def resizeEvent(self, event):
        digitsWidth = self.width() / 2
        digitsHeight = digitsWidth * 1.2

        y = (self.height() - digitsHeight) / 3

        self.m_hour.resize(digitsWidth, digitsHeight)
        self.m_hour.move(0, y)

        self.m_minute.resize(digitsWidth, digitsHeight)
        self.m_minute.move(self.width() / 2, y)

    def timerEvent(self, event):
        self.updateTime()

    def keyPressEvent(self, event):
        if event.key() == QtCore.Qt.Key_Right:
            self.switchTransition(1)
            event.accept()
        if event.key() == QtCore.Qt.Key_Left:
            self.switchTransition(-1)
            event.accept()

    @QtCore.pyqtSlot()
    def chooseSlide(self):
        self.m_hour.setTransition(0)
        self.m_minute.setTransition(0)
        self.updateTime()

    @QtCore.pyqtSlot()
    def chooseFlip(self):
        self.m_hour.setTransition(1)
        self.m_minute.setTransition(1)
        self.updateTime()

    @QtCore.pyqtSlot()
    def chooseRotate(self):
        self.m_hour.setTransition(2)
        self.m_minute.setTransition(2)
        self.updateTime()


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)

    time = DigiFlip()
    time.resize(320, 240)
    time.show()
    sys.exit(app.exec_())
