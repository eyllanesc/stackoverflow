# import gtk
# gtk.set_interactive(False)
import matplotlib

matplotlib.use('Qt5Agg')


import seaborn as sns

import matplotlib.pyplot as plt

plt.style.use('ggplot')

from PyQt5 import QtWidgets, QtCore

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class MyMplCanvas(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        self.fig = Figure(figsize=(width, height), dpi=dpi)

        self.compute_initial_figure()

        FigureCanvas.__init__(self, self.fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtWidgets.QSizePolicy.Expanding,
                                   QtWidgets.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    def compute_initial_figure(self):
        pass


class RegressionPlot(MyMplCanvas):
    def __init__(self, parent=None):

        MyMplCanvas.__init__(self, parent=parent, width=3, height=1, dpi=100)

    def updateGraph(self, dataframe, x_vars, y_var):
        # sns.pairplot(data, ax=self.axes, x_vars=['TV', 'Radio', 'Newspaper'],
        #             y_vars='Sales', size=7, aspect=0.7, kind='reg')
        self.fig.clf()
        self.draw()
        for i in range(len(x_vars)):
            axes = self.fig.add_subplot(1, len(x_vars), i+1)
            sns.regplot(ax=axes, x=dataframe[x_vars[i]], y=dataframe[y_var])

        self.draw()

    def minimumSizeHint(self):
        return QtCore.QSize(500, 400)
