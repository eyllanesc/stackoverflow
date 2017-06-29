# -*- coding: utf-8 -*-

import sys

import pandas as pd
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QVBoxLayout, QWidget, QMainWindow, QLabel, QHBoxLayout, QTableView, \
    QHeaderView

from CustomPages import FirstPage, SecongPage, ThirdPage
from PandasModel import PandasModel
from PlotWidget import RegressionPlot, BarPlot
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

        self.fpage = FirstPage()
        container.addPage(self.fpage)

        self.spage = SecongPage()
        container.addPage(self.spage)

        tpage = ThirdPage()
        container.addPage(tpage)

        self.regressionWidget = RegressionPlot()
        self.layout().addWidget(self.regressionWidget)

        self.barWidget = BarPlot()
        self.layout().addWidget(self.barWidget)
        self.barWidget.hide()

        self.spage.oneComboBox.currentIndexChanged.connect(self.changeRegressionDraw)
        self.spage.finished.connect(self.changeBarDraw)

        self.layout().addWidget(QLabel("some text"))

        self.spage.changeCkeckbox.connect(self.changeRegressionDraw)

        container.changedPage.connect(self.onChangePage)

        self.fpage.changeFilename.connect(self.loadData)

    def onChangePage(self, w):
        if w == self.spage:
            if isinstance(self.df, pd.DataFrame):
                self.regressionWidget.show()
                self.barWidget.hide()

        elif w == self.fpage:
            self.df = None

    def loadData(self, filename):
        print filename
        self.df = pd.read_csv(filename)
        model = PandasModel(self.df)
        self.tableview.setModel(model)
        self.tableview.setColumnHidden(0, True)
        visible_headers = [self.tableview.model().headerData(i, Qt.Horizontal)
                           for i in range(1, self.tableview.model().columnCount())]

        self.spage.setFields(visible_headers)
        self.changeRegressionDraw()

    def changeRegressionDraw(self):
        x_vars = []

        y_var = self.spage.oneComboBox.currentText()

        for btn in self.spage.checkboxs:
            if btn.isChecked() and btn.text() != y_var:
                x_vars.append(btn.text())

        self.regressionWidget.updateGraph(self.df, x_vars, y_var)
        self.regressionWidget.show()
        self.barWidget.hide()

    def changeBarDraw(self):
        df = pd.DataFrame({'a': 10, 'b': 20, 'c': 30}, index=[0])
        self.barWidget.updatePlot(df)
        self.barWidget.show()
        self.regressionWidget.hide()


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setCentralWidget(Widget())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWindow()
    w.showFullScreen()
    sys.exit(app.exec_())
