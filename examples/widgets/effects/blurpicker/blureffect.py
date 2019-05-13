from PyQt5 import QtWidgets


class BlurEffect(QtWidgets.QGraphicsBlurEffect):
    def __init__(self, item):
        super().__init__()
        self.m_baseLine = 200
        self.item = item

    def setBaseLine(self, y):
    	self.m_baseLine = y

    def adjustForItem(self):
        y = self.m_baseLine - self.item.pos().y()
        radius = max(0, min(y / 32, 16))
        self.setBlurRadius(radius)

    def boundingRect(self):
        self.adjustForItem()
        return super().boundingRect()

    def draw(self, painter):
        self.adjustForItem()
        super().draw(painter)
