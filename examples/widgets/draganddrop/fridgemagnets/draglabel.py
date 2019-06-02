from PyQt5 import QtCore, QtGui, QtWidgets


class DragLabel(QtWidgets.QLabel):
    def __init__(self, text, parent=None):
        super(DragLabel, self).__init__(parent)
        metric = QtGui.QFontMetrics(self.font())
        size = metric.size(QtCore.Qt.TextSingleLine, text)

        image = QtGui.QImage(
            size.width() + 12,
            size.height() + 12,
            QtGui.QImage.Format_ARGB32_Premultiplied,
        )
        image.fill(QtGui.qRgba(0, 0, 0, 0))

        font = QtGui.QFont()
        font.setStyleStrategy(QtGui.QFont.ForceOutline)

        gradient = QtGui.QLinearGradient(0, 0, 0, image.height() - 1)
        gradient.setColorAt(0.0, QtCore.Qt.white)
        gradient.setColorAt(0.2, QtGui.QColor(200, 200, 255))
        gradient.setColorAt(0.8, QtGui.QColor(200, 200, 255))
        gradient.setColorAt(1.0, QtGui.QColor(127, 127, 200))

        painter = QtGui.QPainter()
        painter.begin(image)
        painter.setRenderHint(QtGui.QPainter.Antialiasing)
        painter.setBrush(gradient)
        painter.drawRoundedRect(
            QtCore.QRectF(0.5, 0.5, image.width() - 1, image.height() - 1),
            25,
            25,
            QtCore.Qt.RelativeSize,
        )

        painter.setFont(font)
        painter.setBrush(QtCore.Qt.black)
        painter.drawText(
            QtCore.QRect(QtCore.QPoint(6, 6), size), QtCore.Qt.AlignCenter, text
        )
        painter.end()

        self.setPixmap(QtGui.QPixmap.fromImage(image))
        self.m_labelText = text

    def labelText(self):
        return self.m_labelText
