from PyQt5 import QtCore, QtGui, QtWidgets


class FadeMessage(QtWidgets.QGraphicsView):
    def __init__(self, parent=None):
        super(FadeMessage, self).__init__(parent)
        self.m_scene = QtWidgets.QGraphicsScene(self)
        self.setScene(self.m_scene)
        self.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)

        self.setupScene()

        self.m_animation = QtCore.QPropertyAnimation(
            self.m_effect, b"strength", self
        )

    @QtCore.pyqtSlot()
    def togglePopup(self):
        if self.m_message.isVisible():
            self.m_message.setVisible(False)
            self.m_animation.setDirection(QtCore.QAbstractAnimation.Backward)
        else:
            self.m_message.setVisible(True)
            self.m_animation.setDirection(QtCore.QAbstractAnimation.Forward)
        self.m_animation.start()

    def setupScene(self):
        parent = self.m_scene.addRect(0, 0, 800, 600)
        parent.setPen(QtGui.QPen(QtCore.Qt.NoPen))
        parent.setZValue(0)

        bg = self.m_scene.addPixmap(QtGui.QPixmap(":/background.jpg"))
        bg.setParentItem(parent)
        bg.setZValue(1)

        for i in range(5):
            for j in range(2, 5):
                item = self.m_scene.addRect(i * 50, (j - 1) * 50, 38, 38)
                item.setParentItem(parent)
                item.setZValue(1)
                hue = 12 * (i * 5 + j)
                item.setBrush(QtGui.QColor.fromHsv(hue, 128, 128))

        font = QtGui.QFont()
        font.setPointSize(font.pointSize() * 2)
        font.setBold(True)
        fontMetrics = QtGui.QFontMetrics(font)
        fh = fontMetrics.height()

        sceneText = "Qt Everywhere!"
        sceneTextWidth = fontMetrics.horizontalAdvance(sceneText)

        block = self.m_scene.addRect(50, 300, sceneTextWidth, fh + 3)
        block.setPen(QtGui.QPen(QtCore.Qt.NoPen))
        block.setBrush(QtGui.QColor(102, 152, 51))

        text = self.m_scene.addText(sceneText, font)
        text.setDefaultTextColor(QtCore.Qt.white)
        text.setPos(50, 300)
        block.setZValue(2)
        block.hide()

        text.setParentItem(block)
        self.m_message = block

        self.m_effect = QtWidgets.QGraphicsColorizeEffect()
        self.m_effect.setColor(QtGui.QColor(122, 193, 66))
        self.m_effect.setStrength(0)
        self.m_effect.setEnabled(True)
        parent.setGraphicsEffect(self.m_effect)

        press = QtWidgets.QPushButton()
        press.setText(self.tr("Press me"))
        press.clicked.connect(self.togglePopup)
        self.m_scene.addWidget(press)

        press.move(300, 500)

import fademessage_qrc