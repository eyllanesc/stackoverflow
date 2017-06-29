# -*- coding: utf-8 -*-

import sys

import pandas as pd
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QVBoxLayout, QWidget, QMainWindow, QLabel, QHBoxLayout, QListView, QTableView, \
    QAbstractScrollArea, QHeaderView

from CustomPages import FirstPage, SecongPage, ThirdPage
from PandasModel import PandasModel
from PlotPandasWidget import RegressionPlot
from libPage.Pages import ContainerPages


class Widget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent=parent)

        self.df = None

        self.setLayout(QVBoxLayout())

        hbox = QHBoxLayout()
        self.layout().addLayout(hbox)

        container = ContainerPages()

        self.tableview = QTableView(self)
        self.tableview.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableview.setAlternatingRowColors(True)
        hbox.addWidget(container)
        hbox.addWidget(self.tableview)
        hbox.setStretch(0, 1)
        hbox.setStretch(1, 1)

        fpage = FirstPage()
        container.addPage(fpage)
        fpage.changeFilename.connect(self.loadData)

        self.spage = SecongPage()
        container.addPage(self.spage)

        tpage = ThirdPage()
        container.addPage(tpage)

        self.plotWidget = RegressionPlot()
        self.layout().addWidget(self.plotWidget)
        self.spage.oneComboBox.currentIndexChanged.connect(self.changeDraw)

        self.layout().addWidget(QLabel("some text"))

    def loadData(self, filename):
        self.df = pd.read_csv(filename)
        model = PandasModel(self.df)
        self.tableview.setModel(model)
        self.tableview.setColumnHidden(0, True)
        visible_headers = [self.tableview.model().headerData(i, Qt.Horizontal)
                           for i in range(1, self.tableview.model().columnCount())]

        self.spage.setFields(visible_headers)
        self.changeDraw()

    def changeDraw(self):
        visible_headers = [self.tableview.model().headerData(i, Qt.Horizontal)
                           for i in range(1, self.tableview.model().columnCount())]

        y_var = self.spage.oneComboBox.currentText()
        visible_headers.remove(y_var)
        x_vars = visible_headers
        self.plotWidget.updateGraph(self.df, x_vars, y_var)


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setCentralWidget(Widget())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
