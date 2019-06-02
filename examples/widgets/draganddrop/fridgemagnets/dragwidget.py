from PyQt5 import QtCore, QtGui, QtWidgets

from draglabel import DragLabel

def fridgetMagnetsMimeType():
	return "application/x-fridgemagnet"

class DragWidget(QtWidgets.QWidget):
	def __init__(self, parent=None):
		super(DragWidget, self).__init__(parent)
		dictionaryFile = QtCore.QFile(":/dictionary/words.txt")
		dictionaryFile.open(QtCore.QFile.ReadOnly)
		inputStream = QtCore.QTextStream(dictionaryFile)

		x, y = 5, 5

		while not inputStream.atEnd():
			word = inputStream.readLine()
			if word:
				wordLabel = DragLabel(word, self)
				wordLabel.move(x, y)
				wordLabel.show()
				wordLabel.setAttribute(QtCore.Qt.WA_DeleteOnClose)
				x += wordLabel.width() + 2
				if x >= 245:
					x = 5
					y += wordLabel.height() + 2

		newPalette = self.palette()
		newPalette.setColor(QtGui.QPalette.Window, QtCore.Qt.white)
		self.setPalette(newPalette)

		self.setMinimumSize(400, max(200, y))
		self.setWindowTitle(self.tr("Fridge Magnets"))
		self.setAcceptDrops(True)

	def dragEnterEvent(self, event):
		if event.mimeData().hasFormat(fridgetMagnetsMimeType()):
			if event.source() in self.children():
				event.setDropAction(QtCore.Qt.MoveAction)
				event.accept()
			else:
				event.acceptProposedAction()
		elif event.mimeData().hasText():
			event.acceptProposedAction()
		else:
			event.ignore()

	def dragMoveEvent(self, event):
		if event.mimeData().hasFormat(fridgetMagnetsMimeType()):
			if event.source() in self.children():
				event.setDropAction(QtCore.Qt.MoveAction)
				event.accept()
			else:
				event.acceptProposedAction()
		elif event.mimeData().hasText():
			event.acceptProposedAction()
		else:
			event.ignore()

	def dropEvent(self, event):
		if event.mimeData().hasFormat(fridgetMagnetsMimeType()):
			mime = event.mimeData()
			itemData = mime.data(fridgetMagnetsMimeType())
			dataStream = QtCore.QDataStream(itemData, QtCore.QIODevice.ReadOnly)
			text = ""
			offset = QtCore.QPoint()
			text = dataStream.readQString()
			dataStream >> offset
			newLabel = DragLabel(text, self)
			newLabel.move(event.pos() - offset)
			newLabel.show()
			newLabel.setAttribute(QtCore.Qt.WA_DeleteOnClose)

			if event.source() is self:
				event.setDropAction(QtCore.Qt.MoveAction)
				event.accept()
			else:
				event.acceptProposedAction()
		elif event.mimeData().hasText():
			text = event.mimeData().text()
			re = QtCore.QRegularExpression(r"\\s+")
			pieces = []
			iterator = re.globalMatch(text)
			start, end = 0, 0
			while iterator.hasNext():
				match = iterator.next()
				end = match.capturedStart()
				pieces.append(text[start: end - start])
				start = match.capturedEnd()
			pieces.append(text[start: end - start])
			position = event.pos()
			for piece in pieces:
				newLabel = DragLabel(piece, self)
				newLabel.move(position)
				newLabel.show()
				newLabel.setAttribute(QtCore.Qt.WA_DeleteOnClose)

				position += QtCore.QPoint(newLabel.width(), 0)
			event.acceptProposedAction()
		else:
			event.ignore()

	def mousePressEvent(self, event):
		child = self.childAt(event.pos())
		if not isinstance(child, DragLabel):
			return

		hotSpot = event.pos() - child.pos()

		itemData = QtCore.QByteArray()
		dataStream = QtCore.QDataStream(itemData, QtCore.QIODevice.WriteOnly)
		dataStream.writeQString(child.labelText())
		dataStream << QtCore.QPoint(hotSpot)

		mimeData = QtCore.QMimeData()
		mimeData.setData(fridgetMagnetsMimeType(), itemData)
		mimeData.setText(child.labelText())

		drag = QtGui.QDrag(self)
		drag.setMimeData(mimeData)
		drag.setPixmap(child.pixmap())
		drag.setHotSpot(hotSpot)

		child.hide()

		if drag.exec_(QtCore.Qt.MoveAction | QtCore.Qt.CopyAction, QtCore.Qt.CopyAction) == QtCore.Qt.MoveAction:
			child.close()
		else:
			child.show()

import fridgemagnets_qrc