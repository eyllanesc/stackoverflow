import sys

from PyQt5.QtCore import QRect
from PyQt5.QtWidgets import QApplication, QMainWindow, QProxyStyle, QStyle

from tmp.design import Ui_MainWindow


class Style(QProxyStyle):
    def __init__(self, width, parent=None):
        QProxyStyle.__init__(self, parent)
        self._width = width

    def subControlRect(self, cc, opt, sc, widget):
        rect = QProxyStyle.subControlRect(self, cc, opt, sc, widget)
        if cc == QStyle.CC_Slider:
            if sc == QStyle.SC_SliderHandle:
                rect.moveLeft(rect.x()-self._width/2)
                rect.setWidth(self._width)
        return rect


class RPTApp(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(RPTApp, self).__init__(parent)
        self.setupUi(self)
        self.PS_timeSlider.setStyle(Style(100))


def main():
    app = QApplication(sys.argv)
    window = RPTApp()
    window.show()
    app.exec_()


if __name__ == '__main__':
    main()