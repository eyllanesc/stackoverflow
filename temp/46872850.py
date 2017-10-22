import sys
from PySide.QtCore import *
from PySide.QtGui import *


class TextEditor(QTextEdit):
    def __init__(self, parent=None, text=None):
        super().__init__(parent)
        self.setReadOnly(True)
        self.setText(text)
        self.setMouseTracking(True)  # Not sure if I will need this

    def mousePressEvent(self, event):
        if event.buttons() == Qt.LeftButton:
            modifiers = QApplication.keyboardModifiers()
            if modifiers == Qt.ShiftModifier:
                print("Shift+Left Click")  # This never triggers
        super().mousePressEvent(event)

    def mouseMoveEvent(self, event):
        if event.buttons() == Qt.LeftButton:
            modifiers = QApplication.keyboardModifiers()
            if modifiers == Qt.ShiftModifier:
                print("Move and Shift + Left Button")  # This never triggers
        super().mouseMoveEvent(event)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = TextEditor(text="Faction leaders unanimously decided to form a parliamentary inquiry committee...")
    window.show()

    sys.exit(app.exec_())
