from PyQt5.QtCore import *
from PyQt5.QtWidgets import *


class ReadTable2ListProxyModel(QIdentityProxyModel):
    def columnCount(self, parent=QModelIndex()):
        return 1

    def rowCount(self, parent=QModelIndex()):
        return self.sourceModel().rowCount() * self.sourceModel().columnCount()

    def mapFromSource(self, sourceIndex):
        if sourceIndex.isValid() and sourceIndex.column() == 0 \
                and sourceIndex.row() < self.rowCount():
            r = sourceIndex.row()
            c = sourceIndex.column()
            row = c * sourceIndex.model().columnCount() + r
            return self.index(row, 0)
        return QModelIndex()

    def mapToSource(self, proxyIndex):
        r = proxyIndex.row() / self.sourceModel().columnCount()
        c = proxyIndex.row() % self.sourceModel().columnCount()
        return self.sourceModel().index(r, c)

    def index(self, row, column, parent=QModelIndex()):
        return self.createIndex(row, column)


class DuplicateFilterProxyModel(QSortFilterProxyModel):
    def setSourceModel(self, model):
        model.dataChanged.connect(lambda: self.invalidate())
        QSortFilterProxyModel.setSourceModel(self, model)

    def filterAcceptsRow(self, row, parent):
        value = self.sourceModel().index(row, self.filterKeyColumn()) \
            .data(self.filterRole())
        if value is None:
            return False
        if row == 0:
            return True
        for i in reversed(range(0, row)):
            val = self.sourceModel().index(i, self.filterKeyColumn()) \
                .data(self.filterRole())
            if val == value:
                return False
        return True


class TableItemCompleter(QStyledItemDelegate):
    def createEditor(self, parent, option, index):
        editor = QLineEdit(parent)
        completer = QCompleter(parent)

        proxy1 = ReadTable2ListProxyModel(parent)
        proxy2 = DuplicateFilterProxyModel(parent)
        proxy1.setSourceModel(index.model())
        proxy2.setSourceModel(proxy1)

        completer.setModel(proxy2)
        editor.setCompleter(completer)
        return editor


class TitleWidget(QWidget):
    def __init__(self, title, w, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        lay = QVBoxLayout(self)
        lay.addWidget(QLabel(title))
        lay.addWidget(w)


class Widget(QWidget):
    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        splitter = QSplitter(self)
        lay = QHBoxLayout(self)
        lay.addWidget(splitter)
        tv = QTableWidget(3, 4, self)
        lv1 = QListView(self)
        lv2 = QListView(self)

        for i in range(tv.rowCount()):
            for j in range(tv.columnCount()):
                tv.setItem(i, j, QTableWidgetItem(f"{i},{j}"))
        tv.setItemDelegate(TableItemCompleter(tv))

        model1 = ReadTable2ListProxyModel()
        model1.setSourceModel(tv.model())
        lv1.setModel(model1)

        model2 = DuplicateFilterProxyModel()
        model2.setSourceModel(model1)

        lv2.setModel(model2)
        splitter.addWidget(TitleWidget("TableWidget",tv))
        splitter.addWidget(TitleWidget("ReadTable2ListProxyModel", lv1))
        splitter.addWidget(TitleWidget("DuplicateFilterProxyModel", lv2))


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())
