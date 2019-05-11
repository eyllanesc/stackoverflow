from Qt import QtCore, QtGui

from dataclasses import dataclass


@dataclass
class Block:
    rect: QtCore.QRect
    color: QtGui.QColor
