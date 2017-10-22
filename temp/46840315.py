from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class ShrinkExpandButton(QPushButton):
    def __init__(self, *args, **kwargs):
        QPushButton.__init__(self, *args, **kwargs)
        self.setSizePolicy(QSizePolicy.Maximum, QSizePolicy.Expanding)
        self.setFixedWidth(2*self.fontMetrics().height())

    def paintEvent(self, event):
        painter = QStylePainter(self)
        painter.rotate(-90)
        painter.translate(-self.height(), 0)
        option = QStyleOptionButton()
        self.initStyleOption(option)
        size = option.rect.size()
        size.transpose()
        option.rect.setSize(size)
        painter.drawControl(QStyle.CE_PushButton, option)


class ShrinkExpandWidget(QWidget):
    def __init__(self, leftWidget, rightWiget, text, parent=None):
        QWidget.__init__(self, parent)
        button = ShrinkExpandButton(text, self)

        self.setLayout(QHBoxLayout())
        self.layout().setSpacing(0)
        self.layout().addWidget(leftWidget)
        self.layout().addWidget(button)
        self.layout().addWidget(rightWiget)
        leftWidget.setSizePolicy(QSizePolicy.Maximum, QSizePolicy.Expanding)
        button.clicked.connect(lambda: leftWidget.setVisible(not leftWidget.isVisible()))


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    listWidget = QListWidget()
    for i in range(20):
        listWidget.addItem("{}".format(i))

    tableWidget = QTableWidget()
    tableWidget.setColumnCount(10)
    tableWidget.setRowCount(20)
    for i in range(tableWidget.rowCount()):
        for j in range(tableWidget.columnCount()):
            tableWidget.setItem(i, j, QTableWidgetItem("({}, {})".format(i, j)))
    listWidget.setFixedWidth(240)
    w = ShrinkExpandWidget(listWidget, tableWidget, "Shrink - Expand")
    w.resize(720, 480)
    w.show()
    sys.exit(app.exec_())
