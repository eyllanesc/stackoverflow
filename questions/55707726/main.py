import os
from PyQt4 import QtCore, QtGui

root_path = os.path.dirname(os.path.realpath(__file__))
icons_path = file = os.path.join(root_path, "icons")


class MaterialCheckBox(QtGui.QWidget):
    clicked = QtCore.pyqtSignal()
    toggled = QtCore.pyqtSignal(bool)

    def __init__(self, parent=None):
        super(MaterialCheckBox, self).__init__(parent)
        self._is_checked = False

        checkedIcon = MaterialIcon(
            self, os.path.join(icons_path, "baseline-check_box-24px.svg")
        )
        uncheckedIcon = MaterialIcon(
            self,
            os.path.join(
                icons_path, "baseline-check_box_outline_blank-24px.svg"
            ),
        )

        stateMachine = QtCore.QStateMachine(self)

        checkedState = QtCore.QState()
        checkedState.assignProperty(self, b"checked", True)
        checkedState.assignProperty(checkedIcon, b"opacity", 1.0)
        checkedState.assignProperty(uncheckedIcon, b"opacity", 0.0)

        uncheckedState = QtCore.QState()
        uncheckedState.assignProperty(self, b"checked", False)
        uncheckedState.assignProperty(checkedIcon, b"opacity", 0.0)
        uncheckedState.assignProperty(uncheckedIcon, b"opacity", 1.0)

        stateMachine.addState(checkedState)
        stateMachine.addState(uncheckedState)
        stateMachine.setInitialState(uncheckedState)

        duration = 2000

        transition1 = checkedState.addTransition(self.clicked, uncheckedState)
        animation1 = QtCore.QPropertyAnimation(
            checkedIcon, b"opacity", self, duration=duration
        )
        transition1.addAnimation(animation1)
        animation2 = QtCore.QPropertyAnimation(
            uncheckedIcon, b"opacity", self, duration=duration
        )
        transition1.addAnimation(animation2)

        transition2 = uncheckedState.addTransition(self.clicked, checkedState)
        animation3 = QtCore.QPropertyAnimation(
            checkedIcon, b"opacity", self, duration=duration
        )
        transition2.addAnimation(animation3)
        animation4 = QtCore.QPropertyAnimation(
            uncheckedIcon, b"opacity", self, duration=duration
        )
        transition2.addAnimation(animation4)

        stateMachine.start()

    def sizeHint(self):
        return QtCore.QSize(24, 24)

    def isChecked(self):
        return self._is_checked

    def setChecked(self, value):
        if self._is_checked != value:
            self._is_checked = value
            self.toggled.emit(self._is_checked)

    checked = QtCore.pyqtProperty(
        bool, fget=isChecked, fset=setChecked, notify=toggled
    )

    def mousePressEvent(self, event):
        self.clicked.emit()
        self.update()
        super(MaterialCheckBox, self).mousePressEvent(event)


class MaterialIcon(QtGui.QWidget):
    opacityChanged = QtCore.pyqtSignal()

    def __init__(self, parent, address):
        super(MaterialIcon, self).__init__(parent)
        self.icon = QtGui.QPixmap(address)
        self._opacity = 0.0

    def opacity(self):
        return self._opacity

    def setOpacity(self, o):
        if o != self._opacity:
            self._opacity = o
            self.opacityChanged.emit()
            self.update()

    opacity = QtCore.pyqtProperty(
        float, fget=opacity, fset=setOpacity, notify=opacityChanged
    )

    def paintEvent(self, event):
        painter = QtGui.QPainter(self)
        painter.setOpacity(self.opacity)
        mask = QtGui.QPainter(self.icon)
        mask.setCompositionMode(QtGui.QPainter.CompositionMode_SourceIn)
        mask.fillRect(self.icon.rect(), QtGui.QColor(0, 158, 227))
        mask.end()
        painter.drawPixmap(0, 0, self.icon)


if __name__ == "__main__":
    import sys

    app = QtGui.QApplication(sys.argv)
    w = MaterialCheckBox()
    w.show()
    sys.exit(app.exec_())
