from PyQt5.QtCore import *
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import *


class Widget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setLayout(QVBoxLayout())
        self.btn = QPushButton("Add", self)
        sc = QScrollArea(self)
        self.area = QWidget()
        self.layout().addWidget(self.btn)
        self.layout().addWidget(sc)
        sc.setWidget(self.area)
        sc.setWidgetResizable(True)
        self.area.setLayout(QVBoxLayout())
        self.btn.clicked.connect(self.onClicked)

    def onClicked(self):
        path = QStandardPaths.standardLocations(QStandardPaths.PicturesLocation)[0]
        pictures, _ = QFileDialog.getOpenFileNames(self, "Select Images", path, "Image Files (*.png *.jpg *.bmp)")
        for picture in pictures:
            label = QLabel(self)
            label.setPixmap(QPixmap(picture))
            self.area.layout().addWidget(label)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())