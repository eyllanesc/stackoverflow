from PySide.QtGui import *


class Widget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setLayout(QVBoxLayout())
        combobox = QComboBox(self)
        self.layout().addWidget(combobox)

        model = QStandardItemModel()
        combobox.setModel(model)

        view = QListView(self)
        combobox.setView(view)
        view.setViewMode(QListView.IconMode)
        view.setFlow(QListView.LeftToRight)
        view.setResizeMode(QListView.Adjust)
        for i in range(10):
            item = QStandardItem(QIcon("/home/eyllanesc/Downloads/if_cheshire_cat_60814.png"),
                                 "item {}".format(i))
            model.appendRow(item)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())