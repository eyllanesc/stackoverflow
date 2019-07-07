from PyQt5 import QtCore, QtGui, QtWidgets

class LayoutItem(QtWidgets.QGraphicsLayoutItem, QtWidgets.QGraphicsItem):
	def __init__(self, parent=None):
		QtWidgets.QGraphicsLayoutItem.__init__()
		QtWidgets.QGraphicsItem(parent)
		self.m_pix = 