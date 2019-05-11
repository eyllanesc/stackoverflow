from Qt import QtCore, QtGui
import random

from block import Block


class RenderThread(QtCore.QThread):
    sendBlock = QtCore.Signal(Block)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.m_abort = False
        self.mutex = QtCore.QMutex()
        self.m_image = QtGui.QImage()

    def __del__(self):
        self.mutex.lock()
        self.m_abort = True
        self.mutex.unlock()
        # self.wait()

    def processImage(self, image):
        if image.isNull():
            return
        self.m_image = image
        self.m_abort = False
        self.start()

    def run(self):
        size = max(self.m_image.width() // 20, self.m_image.height() // 20)
        for s in range(size, -1, -1):
            for c in range(400):
                x1 = max(0, random.randint(0, self.m_image.width()) - s // 2)
                x2 = min(x1 + s // 2 + 1, self.m_image.width())
                y1 = max(0, random.randint(0, self.m_image.height()) - s // 2)
                y2 = min(y1 + s // 2 + 1, self.m_image.height())
                n = 0
                red = 0
                green = 0
                blue = 0
                for i in range(y1, y2):
                    for j in range(x1, x2):
                        pixel = self.m_image.pixel(j, i)
                        red += QtGui.qRed(pixel)
                        green += QtGui.qGreen(pixel)
                        blue += QtGui.qBlue(pixel)
                        n += 1
                block = Block(
                    QtCore.QRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1),
                    QtGui.QColor(red / n, green / n, blue / n),
                )
                self.sendBlock.emit(block)
                if self.m_abort:
                    return
                QtCore.QThread.msleep(10)

    @QtCore.Slot()
    def stopProcess(self):
        self.mutex.lock()
        self.m_abort = True
        self.mutex.unlock()
