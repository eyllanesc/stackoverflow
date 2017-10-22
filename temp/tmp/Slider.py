from PyQt5.QtCore import QRect, Qt
from PyQt5.QtGui import QPainter, QBrush
from PyQt5.QtWidgets import QSlider, QStyleOptionSlider, QStyle


class Slider(QSlider):
    def paintEvent(self, event):

        p = QPainter(self)
        opt = QStyleOptionSlider()
        self.initStyleOption(opt)
        opt.subControls = QStyle.SC_SliderGroove
        self.style().drawComplexControl(QStyle.CC_Slider, opt, p, self)

        if self.tickPosition() != QSlider.NoTicks:
            opt.subControls |= QStyle.SC_SliderTickmarks
        opt.subControls = QStyle.SC_SliderHandle
        self.style().drawComplexControl(QStyle.CC_Slider, opt, p, self)
