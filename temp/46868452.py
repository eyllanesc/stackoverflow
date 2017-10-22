from PyQt4 import QtGui, QtCore


class Widget(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.filterLe = QtGui.QLineEdit(self)
        self.mytreeview = QtGui.QTreeView(self)
        self.setLayout(QtGui.QVBoxLayout())
        self.layout().addWidget(self.filterLe)
        self.layout().addWidget(self.mytreeview)
        self.model = QtGui.QStandardItemModel(self.mytreeview)

        self.proxyModel = QtGui.QSortFilterProxyModel(self.mytreeview)
        self.proxyModel.setSourceModel(self.model)
        self.mytreeview.setSortingEnabled(True)

        # set model
        self.mytreeview.setModel(self.proxyModel)
        self.mytreeview.clicked.connect(self.update_model)
        self.filterLe.textChanged.connect(self.onTextChanged)
        self.initialise_model()

    @QtCore.pyqtSlot(str)
    def onTextChanged(self, text):
        self.proxyModel.setFilterRegExp(text)

    def initialise_model(self):
        for text in ["parent1", "parent2", "parent3"]:
            item = QtGui.QStandardItem(text)
            self.model.appendRow(item)

    def update_model(self, index):
        ix = self.proxyModel.mapToSource(index)
        parent = self.model.itemFromIndex(ix)
        for text in ["children1", "children2", "children3"]:
            children = QtGui.QStandardItem("{}_{}".format(parent.text(), text))
            parent.appendRow(children)
        self.mytreeview.expand(index)


if __name__ == '__main__':
    import sys
    app = QtGui.QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())