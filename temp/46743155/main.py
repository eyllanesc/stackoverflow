from PyQt4.QtCore import *
from PyQt4.QtGui import *
from untitled import *


class PopUp(QDialog):
    def __init__(self, labels):
        QDialog.__init__(self, None, Qt.Popup | Qt.FramelessWindowHint)
        self.itemSelected = ""
        self.setLayout(QVBoxLayout())
        lWidget = QListWidget(self)
        self.layout().addWidget(lWidget)
        lWidget.addItems(labels)
        lWidget.itemClicked.connect(self.onItemClicked)
        self.layout().setContentsMargins(0, 0, 0, 0)

    def onItemClicked(self, item):
        self.itemSelected = item.text()
        self.accept()

    def text(self):
        return self.itemSelected


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.tableWidget.clicked.connect(self.onClicked)

    def onClicked(self, index):
        row = index.row()
        column = index.column()
        x = self.tableWidget.columnViewportPosition(column)
        y = self.tableWidget.rowViewportPosition(row) + self.tableWidget.rowHeight(row)
        pos = self.tableWidget.viewport().mapToGlobal(QPoint(x, y))
        p = PopUp(["1", "2", "3", "4", "5"])
        p.move(pos)
        if p.exec_() == QDialog.Accepted:
            t_item = QTableWidgetItem(p.text())
            self.tableWidget.setItem(row, column, t_item)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())