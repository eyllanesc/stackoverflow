from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QSpacerItem, QSizePolicy, QPushButton


class Page(QWidget):
    finished = pyqtSignal()

    def __init__(self, parent=None):
        QWidget.__init__(self, parent=parent)


class ContainerPages(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent=parent)
        self.centralWidget = QWidget()
        self.setLayout(QVBoxLayout())
        self.listWidgets = []
        self.layout().addWidget(self.centralWidget)
        self.currentIndex = -1

        hbox = QHBoxLayout()
        item = QSpacerItem(1, 1, QSizePolicy.Expanding, QSizePolicy.Fixed)
        hbox.addItem(item)
        self.backBtn = QPushButton("Back")
        hbox.addWidget(self.backBtn)
        self.layout().addLayout(hbox)

        self.backBtn.clicked.connect(self.backPage)

    def backPage(self):
        index = self.currentIndex - 1
        if index >= 0:
            self.changeWidget(index)

    def nextPage(self):
        index = self.currentIndex + 1
        if index < len(self.listWidgets):
            self.changeWidget(index)

    def addPage(self, w):
        if isinstance(w, Page):
            self.listWidgets.append(w)
            w.finished.connect(self.nextPage)
        else:
            print("La clase debe heredar de Page")

    def changeWidget(self, index):
        self.centralWidget.hide()
        self.layout().replaceWidget(self.centralWidget, self.listWidgets[index])
        self.currentIndex = index
        if self.currentIndex == 0:
            self.backBtn.hide()
        else:
            self.backBtn.show()
        self.centralWidget = self.listWidgets[self.currentIndex]
        self.centralWidget.show()
        print(self.currentIndex)

    def showEvent(self, event):
        if self.currentIndex == -1:
            self.currentIndex = 0
        self.changeWidget(self.currentIndex)
        QWidget.showEvent(self, event)