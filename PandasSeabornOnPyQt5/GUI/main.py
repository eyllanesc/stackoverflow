# -*- coding: utf-8 -*-

import sys

import pandas as pd
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QVBoxLayout, QWidget, QMainWindow, QLabel, QHBoxLayout, QTableView, \
    QHeaderView
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

from CustomPages import FirstPage, SecongPage, ThirdPage
from PandasModel import PandasModel
from PlotWidget import RegressionPlot, BarPlot
from libPage import ContainerPages


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

        self.tpage = ThirdPage()
        container.addPage(self.tpage)

        self.regressionWidget = RegressionPlot()
        self.layout().addWidget(self.regressionWidget)

        self.barWidget = BarPlot()
        self.layout().addWidget(self.barWidget)
        self.barWidget.hide()

        self.spage.oneComboBox.currentIndexChanged.connect(self.changeRegressionDraw)
        self.spage.finished.connect(self.changeBarDraw)

        self.layout().addWidget(QLabel("some text"))

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

        for label in self.spage.labels:
            if label.text() != y_var:
                x_vars.append(label.text())

        self.regressionWidget.updateGraph(self.df, x_vars, y_var)
        self.regressionWidget.show()
        self.barWidget.hide()

    def changeBarDraw(self):
        x_vars = []
        y_var = self.spage.oneComboBox.currentText()
        for label in self.spage.labels:
            if label.text() != y_var:
                x_vars.append(label.text())

        y = self.df[y_var]
        x = self.df[x_vars]

        x_train, x_test, y_train, y_test = train_test_split(x, y, random_state=1)

        lin_reg = LinearRegression()
        lin_reg.fit(x_train, y_train)

        co_dict = {}
        for i in range(len(lin_reg.coef_)):
            co_dict[x_vars[i]] = float(round(lin_reg.coef_[i] * 1000, 1))
        results_df = pd.DataFrame(co_dict, index=['Sales'])

        interpretation = "Interpretation:For a given amount of ad spending, " \
                         "an additional $1,000 spent will likely increase unit sales by:"
        self.tpage.setText(lin_reg.intercept_,
                           co_dict.values(),
                           interpretation,
                           y_var,
                           zip(x, [co_dict[var] for var in x]))
        self.barWidget.updatePlot(results_df)
        self.barWidget.show()
        self.regressionWidget.hide()


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)
        self.setWindowTitle("Title")
        self.setCentralWidget(Widget())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWindow()
    w.showMaximized()
    sys.exit(app.exec_())
