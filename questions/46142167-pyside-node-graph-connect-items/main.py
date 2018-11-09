import sys
from PySide.QtCore import *
from PySide.QtGui import *


class WindowClass(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.view = ViewClass()
        self.setCentralWidget(self.view)


class ViewClass(QGraphicsView):
    def __init__(self, parent=None):
        QGraphicsView.__init__(self, parent)

        self.setDragMode(QGraphicsView.RubberBandDrag)
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)

        self.s = SceneClass()
        self.setScene(self.s)
        self.setRenderHint(QPainter.Antialiasing)


class SceneClass(QGraphicsScene):
    grid = 30

    def __init__(self, parent=None):
        QGraphicsScene.__init__(self, QRectF(-1000, -1000, 2000, 2000), parent)

    def drawBackground(self, painter, rect):
        painter.fillRect(rect, QColor(30, 30, 30))
        left = int(rect.left()) - int((rect.left()) % self.grid)
        top = int(rect.top()) - int((rect.top()) % self.grid)
        right = int(rect.right())
        bottom = int(rect.bottom())
        lines = []
        for x in range(left, right, self.grid):
            lines.append(QLine(x, top, x, bottom))
        for y in range(top, bottom, self.grid):
            lines.append(QLine(left, y, right, y))
        painter.setPen(QPen(QColor(50, 50, 50)))
        painter.drawLines(lines)

    def mouseDoubleClickEvent(self, event):
        node = Node()
        self.addItem(node)
        node.setPos(event.scenePos())
        QGraphicsScene.mouseMoveEvent(self, event)

    def mousePressEvent(self, event):
        if event.button() == Qt.RightButton:
            if len(self.selectedItems()) == 2:
                edge = Edge(self.selectedItems()[0], self.selectedItems()[1])
                self.addItem(edge)
        QGraphicsScene.mousePressEvent(self, event)


class Node(QGraphicsRectItem):
    def __init__(self, rect=QRectF(-75, -15, 150, 30), parent=None):
        QGraphicsRectItem.__init__(self, rect, parent)
        self.edges = []
        self.setZValue(1)
        self.setBrush(Qt.darkGray)
        self.setFlags(QGraphicsItem.ItemIsMovable |
                      QGraphicsItem.ItemIsSelectable |
                      QGraphicsItem.ItemSendsGeometryChanges)

    def addEdge(self, edge):
        self.edges.append(edge)

    def itemChange(self, change, value):
        if change == QGraphicsItem.ItemSelectedChange:
            self.setBrush(Qt.green if value else Qt.darkGray)

        if change == QGraphicsItem.ItemPositionHasChanged:
            for edge in self.edges:
                edge.adjust()

        return QGraphicsItem.itemChange(self, change, value)


class Edge(QGraphicsLineItem):
    def __init__(self, source, dest, parent=None):
        QGraphicsLineItem.__init__(self, parent)
        self.source = source
        self.dest = dest
        self.source.addEdge(self)
        self.dest.addEdge(self)
        self.setPen(QPen(Qt.red, 1.75))
        self.adjust()

    def adjust(self):
        self.prepareGeometryChange()
        self.setLine(QLineF(self.dest.pos(), self.source.pos()))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    wd = WindowClass()
    wd.show()
    sys.exit(app.exec_())
