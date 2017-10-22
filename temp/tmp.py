# !/usr/bin/env python

from PyQt4 import QtGui, QtCore
import sys


class RotatedButton(QtGui.QPushButton):
    def __init__(self, text, parent, orientation="west"):
        super(RotatedButton, self).__init__(text, parent)
        self.orientation = orientation

    def paintEvent(self, event):
        painter = QtGui.QStylePainter(self)
        painter.rotate(90)
        painter.translate(0, -1 * self.width());
        painter.drawControl(QtGui.QStyle.CE_PushButton, self.getSyleOptions())

    def minimumSizeHint(self):
        size = super(RotatedButton, self).minimumSizeHint()
        size.transpose()
        return size

    def sizeHint(self):
        size = super(RotatedButton, self).sizeHint()
        size.transpose()
        return size

    def getSyleOptions(self):
        options = QtGui.QStyleOptionButton()
        options.initFrom(self)
        size = options.rect.size()
        size.transpose()
        options.rect.setSize(size)
        options.features = QtGui.QStyleOptionButton.None_
        if self.isFlat():
            options.features |= QtGui.QStyleOptionButton.Flat
        if self.menu():
            options.features |= QtGui.QStyleOptionButton.HasMenu
        if self.autoDefault() or self.isDefault():
            options.features |= QtGui.QStyleOptionButton.AutoDefaultButton
        if self.isDefault():
            options.features |= QtGui.QStyleOptionButton.DefaultButton
        if self.isDown() or (self.menu() and self.menu().isVisible()):
            options.state |= QtGui.QStyle.State_Sunken
        if self.isChecked():
            options.state |= QtGui.QStyle.State_On
        if not self.isFlat() and not self.isDown():
            options.state |= QtGui.QStyle.State_Raised

        options.text = self.text()
        options.icon = self.icon()
        options.iconSize = self.iconSize()
        return options


class Main(QtGui.QFrame):
    def __init__(self):
        QtGui.QFrame.__init__(self)

        self.application = QtCore.QCoreApplication.instance()
        self.layout = QtGui.QHBoxLayout()
        self.button = RotatedButton("Hello", self, orientation="west")
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)


if __name__ == '__main__':
    application = QtGui.QApplication(sys.argv)
    application.main = Main()
    application.main.show()
    sys.exit(application.exec_())
