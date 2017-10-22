from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import *


class Widget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setLayout(QVBoxLayout())
        combo = QComboBox(self)
        self.layout().addWidget(combo)
        combo.addItems(["item1", "item2", "item3"])
        combo.activated[int].connect(self.onActivatedIndex)
        combo.activated[str].connect(self.onActivatedText)

    @pyqtSlot(int)
    def onActivatedIndex(self, index):
        print(index)

    @pyqtSlot(str)
    def onActivatedText(self, text):
        print(text)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    app.setStyle("fusion")
    w = Widget()
    w.show()
    sys.exit(app.exec_())
