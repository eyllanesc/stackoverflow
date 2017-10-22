from PyQt4 import QtGui


class Widget(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.mytreeview = QtGui.QTreeView(self)
        self.setLayout(QtGui.QVBoxLayout())
        self.layout().addWidget(self.mytreeview)
        self.model = QtGui.QStandardItemModel(self.mytreeview)
        self.mytreeview.setModel(self.model)
        self.mytreeview.clicked.connect(self.update_model)
        self.initialise_model()

    def initialise_model(self):
        for text in ["parent1", "parent2", "parent3"]:
            item = QtGui.QStandardItem(text)
            self.model.appendRow(item)

    def update_model(self, index):
        parent = self.model.itemFromIndex(index)
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
