from PyQt5.QtWidgets import *

app = QApplication([])


class Dialog(QDialog):
    def __init__(self, *args, **kwargs):
        super(Dialog, self).__init__(*args, **kwargs)
        self.setLayout(QVBoxLayout())

        self.tree = QTreeWidget(self)
        self.tree.setHeaderLabels(['Column name'])
        for i in range(3):
            root_item = QTreeWidgetItem()
            root_item.setText(0, 'Root %s' % i)
            self.tree.addTopLevelItem(root_item)
            for n in range(3):
                childItem = QTreeWidgetItem(root_item)
                childItem.setText(0, 'Child %s' % n)
            root_item.setExpanded(True)

        btn = QPushButton(self)
        btn.setText("Delete the selected Root item's child items")
        btn.clicked.connect(self.onClick)
        self.layout().addWidget(self.tree)
        self.layout().addWidget(btn)
        self.show()

    def onClick(self):
        current_item = self.tree.currentItem()
        if not current_item:
            print('Please select root item fist')
        elif not current_item.parent():
            print('Child item is selected. Please select root item instead.')
        else:
            print('Root item selected. Number of children: %r' % current_item.childCount())


tree = Dialog()
app.exec_()