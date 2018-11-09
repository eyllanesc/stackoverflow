from PyQt4 import QtGui


class Widget(QtGui.QWidget):
    def __init__(self, parent=None):
        super(Widget, self).__init__(parent=parent)
        self.layout = QtGui.QVBoxLayout(self)
        self.line = QtGui.QLineEdit()
        self.button = QtGui.QPushButton("Button")
        self.layout.addWidget(self.button)
        self.layout.addWidget(self.line)
        shortcut = QtGui.QShortcut(QtGui.QKeySequence("Ctrl+O"), self)
        shortcut.activated.connect(self.line.setFocus)

if __name__ == '__main__':
    import sys
    app = QtGui.QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())
