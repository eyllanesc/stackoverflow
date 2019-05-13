import math
from PyQt5 import QtCore, QtGui, QtWidgets

from blureffect import BlurEffect

import blurpicker_rc


class BlurPicker(QtWidgets.QGraphicsView):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.m_index = 0.0
        self.m_icons = []
        self.m_animation = QtCore.QPropertyAnimation(self, b"index")

        self.setBackgroundBrush(
            QtGui.QBrush(QtGui.QPixmap(":/images/background.jpg"))
        )
        self.setScene(QtWidgets.QGraphicsScene(self))

        self.setupScene()
        self.setIndex(0)

        self.m_animation.setDuration(400)
        self.m_animation.setEasingCurve(QtCore.QEasingCurve.InOutSine)

        self.setRenderHint(QtGui.QPainter.Antialiasing, True)
        self.setFrameStyle(QtWidgets.QFrame.NoFrame)

    def index(self):
        return self.m_index

    def setIndex(self, index):
        self.m_index = index

        baseline = 0
        iconAngle = 2 * math.pi / len(self.m_icons)
        for i, icon in enumerate(self.m_icons):
            a = (i + self.m_index) * iconAngle
            xs = 170 * math.sin(a)
            ys = 100 * math.cos(a)
            pos = QtCore.QPointF(xs, ys)
            pos = QtGui.QTransform().rotate(-20).map(pos)
            pos -= QtCore.QPointF(40, 40)
            icon.setPos(pos)
            baseline = max(baseline, ys)
            icon.graphicsEffect().setBaseLine(baseline)
        self.scene().update()

    index = QtCore.pyqtProperty(float, fget=index, fset=setIndex)

    def keyPressEvent(self, event):
        delta = 0
        if event.key() == QtCore.Qt.Key_Left:
            delta = -1
        elif event.key() == QtCore.Qt.Key_Right:
            delta = 1

        if (
            self.m_animation.state() == QtCore.QAbstractAnimation.Stopped
            and delta
        ):
            self.m_animation.setEndValue(self.m_index + delta)
            self.m_animation.start()
            event.accept()

    def resizeEvent(self, event):
        pass

    def mousePressEvent(self, event):
        delta = 0
        if event.x() > (self.width() / 2):
            delta = 1
        else:
            delta = -1

        if (
            self.m_animation.state() == QtCore.QAbstractAnimation.Stopped
            and delta
        ):
            self.m_animation.setEndValue(self.m_index + delta)
            self.m_animation.start()
            event.accept()

    def setupScene(self):
        self.scene().setSceneRect(-200, -120, 400, 240)
        names = [
            ":/images/accessories-calculator.png",
            ":/images/accessories-text-editor.png",
            ":/images/help-browser.png",
            ":/images/internet-group-chat.png",
            ":/images/internet-mail.png",
            ":/images/internet-web-browser.png",
            ":/images/office-calendar.png",
            ":/images/system-users.png",
        ]
        for name in names:
            pixmap = QtGui.QPixmap(name)
            icon = self.scene().addPixmap(pixmap)
            icon.setZValue(1)
            icon.setGraphicsEffect(BlurEffect(icon))
            self.m_icons.append(icon)

        bg = self.scene().addPixmap(QtGui.QPixmap(":/images/background.jpg"))
        bg.setZValue(0)
        bg.setPos(-200, -150)
