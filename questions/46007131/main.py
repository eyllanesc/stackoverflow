import sys

from PyQt5.QtCore import Qt, QSize
from PyQt5.QtWidgets import QTabBar, QWidget, QApplication, QPushButton, QTabWidget, QHBoxLayout, QVBoxLayout


class TabBar(QTabBar):
    def tabSizeHint(self, index):
        size = QTabBar.tabSizeHint(self, index)
        w = int(self.width()/self.count())
        return QSize(w, size.height())


class Container(QWidget):
    def __init__(self, text):
        super(Container, self).__init__()

        self.hbox = QHBoxLayout()
        self.hbox.setSpacing(0)
        self.hbox.setContentsMargins(0, 0, 0, 0)
        self.setLayout(self.hbox)

        self.button = QPushButton(text)
        self.hbox.addWidget(self.button)


class CustomWidget (QWidget):
    def __init__(self, parent=None):
        super(CustomWidget, self).__init__(parent)

        self.button = QPushButton("Add tab")
        self.button.clicked.connect(self.buttonClicked)

        self.tabs = QTabWidget()
        self.tabs.setTabBar(TabBar())
        self.tabs.setTabsClosable(True)
        self.tabs.setMovable(True)
        self.tabs.setDocumentMode(True)
        self.tabs.setElideMode(Qt.ElideRight)
        self.tabs.setUsesScrollButtons(True)
        self.tabs.tabCloseRequested.connect(self.closeTab)

        self.tabs.addTab(Container("Very big titleeeeeeeeee"),
                         "Very big titleeeeeeeeeeee")
        self.tabs.addTab(Container("smalltext"), "smalltext")
        self.tabs.addTab(Container("smalltext2"), "smalltext2")

        vbox = QVBoxLayout()
        vbox.addWidget(self.button)
        vbox.addWidget(self.tabs)
        self.setLayout(vbox)

        self.resize(600, 600)

    def closeTab(self, index):
        tab = self.tabs.widget(index)
        tab.deleteLater()
        self.tabs.removeTab(index)

    def buttonClicked(self):
        self.tabs.addTab(Container("smalltext2"), "smalltext2")


app = QApplication([])

app.setStyleSheet("""
    QTabBar::tab:selected {
        background: gray;
        color: white;
    }
""")

widget = CustomWidget()
widget.show()

sys.exit(app.exec_())