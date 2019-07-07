import math
from PyQt5 import QtCore, QtGui, QtWidgets

M_PI = 3.14159265358979323846
WORLD_SIZE = 8
world_map = [
    [1, 1, 1, 1, 6, 1, 1, 1],
    [1, 0, 0, 1, 0, 0, 0, 7],
    [1, 1, 0, 1, 0, 1, 1, 1],
    [6, 0, 0, 0, 0, 0, 0, 3],
    [1, 8, 8, 0, 8, 0, 8, 1],
    [2, 2, 0, 0, 8, 8, 7, 1],
    [3, 0, 0, 0, 0, 0, 0, 5],
    [2, 2, 2, 2, 7, 4, 4, 4],
]

TEXTURE_SIZE = 64
TEXTURE_BLOCK = TEXTURE_SIZE * TEXTURE_SIZE


class Raycasting(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(Raycasting, self).__init__(parent)
        self.angle = 0.5
        self.playerPos = QtCore.QPointF(1.5, 1.5)
        self.angleDelta = 0
        self.moveDelta = 0
        self.touchDevice = False
        self.textureImg = QtGui.QImage()
        self.watch = QtCore.QTime()
        self.ticker = QtCore.QBasicTimer()
        self.buffer = QtGui.QImage()
        self.bufferSize = QtCore.QSize()

        # http://www.areyep.com/RIPandMCS-TextureLibrary.html
        self.textureImg.load(":/textures.png")
        self.textureImg = self.textureImg.convertToFormat(
            QtGui.QImage.Format_ARGB32
        )
        assert self.textureImg.width() == TEXTURE_SIZE * 2
        assert self.textureImg.bytesPerLine() == 4 * TEXTURE_SIZE * 2

        self.textureCount = self.textureImg.height() / TEXTURE_SIZE
        self.watch.start()
        self.ticker.start(25, self)
        self.setAttribute(QtCore.Qt.WA_OpaquePaintEvent, True)
        self.setMouseTracking(False)

    def updatePlayer(self):
        interval = min(max(20, self.watch.elapsed()), 250)
        self.watch.start()
        self.angle += self.angleDelta * interval / 1000
        step = self.moveDelta * interval / 1000
        dx = math.cos(angle) * step
        dy = math.sin(angle) * step

        pos = self.playerPos + 3 * QtCore.QPointF(dx, dy)
        xi = int(pos.x())
        yi = int(pos.y())
        if world_map[xi][yi] == 0:
            self.playerPos += QtCore.QPointF(dx, dy)

    def showFps(self):
        frameTick = QtCore.QTime()
        totalFrame = 0

        if not (totalFrame & 31):
            elapsed = frameTick.elapsed()
            frameTick.start()
            fps = 32 * 1000 / (1 + elapsed)
            self.setWindowTitle("Raycasting (%s FPS)" % (fps,))
        totalFrame += 1

    def render(self):
    	# setup the screen surface
        if self.buffer.size() != self.bufferSize:
            self.buffer = QtGui.QImage(
                self.bufferSize, QtGui.QImage.Format_ARGB32
            )
        bufw = self.buffer.width()
        bufh = self.buffer.height()
        if bufw <= or bufh <= 0:
        	return

        # we intentionally cheat here, to avoid detach
        ptr = self.buffer.bits()
        start = 


import raycasting_rc

if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = Raycasting()
    w.resize(640, 480)
    w.show()

    sys.exit(app.exec_())
