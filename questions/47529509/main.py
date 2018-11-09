from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class TreeView(QTreeView):
    customMimeType = "application/x-customqstandarditemmodeldatalist"

    def __init__(self, *args, **kwargs):
        QTreeView.__init__(self, *args, **kwargs)
        self.setSelectionMode(QAbstractItemView.SingleSelection)
        self.setDragEnabled(True)
        self.viewport().setAcceptDrops(True)
        self.setDropIndicatorShown(True)
        self.setDragDropMode(QTreeView.InternalMove)

    def itemsToPixmap(self, indexes):
        rect = self.viewport().visibleRegion().boundingRect()
        pixmap = QPixmap(rect.size())
        pixmap.fill(Qt.transparent)
        painter = QPainter(pixmap)
        for index in indexes:
            painter.drawPixmap(self.visualRect(index), self.viewport().grab(self.visualRect(index)))
        return pixmap

    def mimeTypes(self):
        mimetypes = QTreeView.mimeTypes(self)
        mimetypes.append(TreeView.customMimeType)
        return mimetypes

    def startDrag(self, supportedActions):
        drag = QDrag(self)
        mimedata = self.model().mimeData(self.selectedIndexes())

        encoded = QByteArray()
        stream = QDataStream(encoded, QIODevice.WriteOnly)
        self.encodeData(self.selectedIndexes(), stream)
        mimedata.setData(TreeView.customMimeType, encoded)

        drag.setMimeData(mimedata)
        px = self.itemsToPixmap(self.selectedIndexes())
        drag.setPixmap(px)
        drag.setHotSpot(self.viewport().mapFromGlobal(QCursor.pos()) - QPoint(self.horizontalOffset(),
                                                                              self.verticalOffset()))
        drag.exec_(supportedActions)

    def encodeData(self, items, stream):
        stream.writeInt32(len(items))
        for item in items:
            p = item
            rows = []
            while p.isValid():
                rows.append(p.row())
                p = p.parent()
            stream.writeInt32(len(rows))
            for row in reversed(rows):
                stream.writeInt32(row)

    def dropEvent(self, event):
        if event.source() == self:
            if event.mimeData().hasFormat(TreeView.customMimeType):
                encoded = event.mimeData().data(TreeView.customMimeType)
                items = self.decodeData(encoded, event.source())
                ix = self.indexAt(event.pos())
                current = self.model().itemFromIndex(ix)
                p = current
                level = 1
                while p:
                    p = p.parent()
                    level += 1
                for item, ilevel in items:
                    if level == ilevel:
                        item.parent().takeRow(item.row())
                        current.appendRow(item)
                self.clearSelection()
                event.acceptProposedAction()
        else:
            event.ignore()

    def decodeData(self, encoded, tree):
        items = []
        rows = []
        stream = QDataStream(encoded, QIODevice.ReadOnly)
        while not stream.atEnd():
            nItems = stream.readInt32()
            for i in range(nItems):
                path = stream.readInt32()
                row = []
                for j in range(path):
                    row.append(stream.readInt32())
                rows.append(row)

        for row in rows:
            it = self.model().item(row[0])
            for r in row[1:]:
                it = it.child(r)
            items.append((it, len(row)))
        return items


elements = {"Africa":
                [{"Vegetables": {"Beans": ["red", "yellow"], "Cucumber": ["big", "small"]}},
                 {"Fruits": {"Banana": ["sweet", "big"], "Coconut": ["plain", "milk"]}}, "Meat", "Drinks"],
            "Asia": ["Vegetables", "Fruits"]}


def addItems(parent, values):
    if isinstance(values, dict):
        for key, value in values.items():
            item = QStandardItem(key)
            parent.appendRow(item)
            addItems(item, value)

    elif isinstance(values, list) or isinstance(values, tuple):
        for value in values:
            if isinstance(value, list) or isinstance(value, dict) or isinstance(value, tuple):
                addItems(parent, value)
            else:
                item = QStandardItem(value)
                parent.appendRow(item)


def createModel(data):
    model = QStandardItemModel()
    addItems(model, data)
    return model


if __name__ == "__main__":
    import sys

    app = QApplication(sys.argv)
    w = TreeView()
    w.setModel(createModel(elements))
    w.expandAll()
    w.show()
    sys.exit(app.exec_())
