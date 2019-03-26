from PyQt5 import QtCore, QtGui, QtWidgets, QtSvg 

class PianoKey(QtWidgets.QGraphicsRectItem):
	def __init__(self, black=False, rect = QtCore.QRectF(), parent=None):
		super(PianoKey, self).__init__(rect, parent)
		self.m_pressed = False
		self.m_selectedBrush = QtGui.QBrush()
		self.m_brush = QtGui.QBrush(QtCore.Qt.black) if black else QtGui.QBrush(QtCore.Qt.white) 
		self.m_black = black

	def setPressedBrush(self, brush):
		self.m_selectedBrush = brush

	def paint(self, painter, option, widget):
		rendered = QtSvg.QSvgRenderer("key.svg")
		black_pen = QtGui.QPen(QtCore.Qt.black, 1)
		gray_pen = QtGui.QPen(QtGui.QBrush(QtCore.Qt.gray), 1, 
			QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin)
		if self.m_pressed:
			if self.m_selectedBrush.style() != QtCore.Qt.NoBrush:
				painter.setBrush(self.m_selectedBrush)
			else:
				painter.setBrush(QtWidgets.QApplication.palette().highlight())
		else: 
			painter.setBrush(self.m_brush);
		painter.setPen(black_pen)
		painter.drawRoundedRect(self.rect(), 15, 15, QtCore.Qt.RelativeSize)
		if self.m_black:
			rendered.render(painter, self.rect())
		else:
			points = [
				QtCore.QPointF(self.rect().left()+1.5, self.rect().bottom()-1),
				QtCore.QPointF(self.rect().right()-1, self.rect().bottom()-1),
				QtCore.QPointF(self.rect().right()-1, self.rect().top()+1)
			]
			painter.setPen(gray_pen)
			painter.drawPolyline(QtGui.QPolygonF(points))

	def mousePressEvent(self, event):
		self.m_pressed = True
		self.update()
		super(PianoKey, self).mousePressEvent(event)
		event.accept()

	def mouseReleaseEvent(self, event):
		self.m_pressed = False
		self.update()
		super(PianoKey, self).mouseReleaseEvent(event)

KEYWIDTH, KEYHEIGHT = 18, 72

class PianoKeyBoard(QtWidgets.QGraphicsView):
	def __init__(self, num_octaves=2,  parent=None):
		super(PianoKeyBoard, self).__init__(parent)
		self.initialize()
		self.m_numOctaves = num_octaves
		scene = QtWidgets.QGraphicsScene(QtCore.QRectF(0, 0, KEYWIDTH * self.m_numOctaves * 7, KEYHEIGHT), self)
		self.setScene(scene)
		numkeys = self.m_numOctaves * 12

		for i in range(numkeys):
			octave = i//12*7
			j = i % 12
			if j >= 5: j += 1
			if j % 2 == 0:
				x = (octave + j/2)*KEYWIDTH
				key = PianoKey(rect=QtCore.QRectF(x, 0, KEYWIDTH, KEYHEIGHT), black=False)
			else:
				x = (octave + j//2) * KEYWIDTH  + KEYWIDTH * 6//10 + 1
				key = PianoKey(rect=QtCore.QRectF(x, 0, KEYWIDTH * 8//10 - 1, KEYHEIGHT * 6//10 ), black=True)
				key.setZValue(1)
			key.setPressedBrush(QtWidgets.QApplication.palette().highlight())
			self.scene().addItem(key)

	def initialize(self):
		self.setAttribute(QtCore.Qt.WA_InputMethodEnabled, False)
		self.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
		self.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
		self.setCacheMode(QtWidgets.QGraphicsView.CacheBackground)
		self.setViewportUpdateMode(QtWidgets.QGraphicsView.MinimalViewportUpdate)
		self.setRenderHints(QtGui.QPainter.Antialiasing|
			QtGui.QPainter.TextAntialiasing | 
			QtGui.QPainter.SmoothPixmapTransform)
		self.setOptimizationFlag(QtWidgets.QGraphicsView.DontClipPainter, True)
		self.setOptimizationFlag(QtWidgets.QGraphicsView.DontSavePainterState, True)
		self.setOptimizationFlag(QtWidgets.QGraphicsView.DontAdjustForAntialiasing, True)
		self.setBackgroundBrush(QtWidgets.QApplication.palette().base())

	def resizeEvent(self, event):
		super(PianoKeyBoard, self).resizeEvent(event)
		self.fitInView(self.scene().sceneRect(), QtCore.Qt.KeepAspectRatio)

	def sizeHint(self):
		return self.mapFromScene(self.sceneRect()).boundingRect().size()

if __name__ == '__main__':
	import sys
	app = QtWidgets.QApplication(sys.argv)
	app.setStyle('fusion')
	w = QtWidgets.QWidget()
	lay = QtWidgets.QVBoxLayout(w)
	lay.addWidget(QtWidgets.QLabel("Piano Keyboard", alignment=QtCore.Qt.AlignCenter))
	lay.addWidget(PianoKeyBoard())
	w.resize(640, 480)
	w.show()
	sys.exit(app.exec_())