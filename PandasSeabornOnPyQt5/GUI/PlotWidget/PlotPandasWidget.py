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

sns.set(color_codes=True)


class MyMplCanvas(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        self.fig = Figure(figsize=(width, height), dpi=dpi)

        FigureCanvas.__init__(self, self.fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtWidgets.QSizePolicy.Expanding,
                                   QtWidgets.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    def minimumSizeHint(self):
        return QtCore.QSize(800, 200)


class RegressionPlot(MyMplCanvas):
    def __init__(self, parent=None):

        MyMplCanvas.__init__(self, parent=parent, width=3, height=1, dpi=80)

    def updateGraph(self, dataframe, x_vars, y_var):
        # sns.pairplot(data, ax=self.axes, x_vars=['TV', 'Radio', 'Newspaper'],
        #             y_vars='Sales', size=7, aspect=0.7, kind='reg')
        self.fig.clear()

        axes = self.fig.add_subplot(1, len(x_vars), 1)
        sns.regplot(ax=axes, x=dataframe[x_vars[0]], y=dataframe[y_var])

        for i in range(1, len(x_vars)):
            ax = self.fig.add_subplot(1, len(x_vars), i+1, sharey=axes)
            sns.regplot(ax=ax, x=dataframe[x_vars[i]], y=dataframe[y_var])
            # axes.get_shared_y_axes().join(axes, ax)

            ax.get_yaxis().set_visible(False)

        self.fig.tight_layout()
        self.draw()


class BarPlot(MyMplCanvas):
    def __init__(self, parent=None):

        MyMplCanvas.__init__(self, parent=parent, width=3, height=1, dpi=80)
        self.ax = self.fig.add_subplot(1, 1, 1)

    def updatePlot(self, dataframe):
        self.ax.clear()
        dataframe.plot(kind='bar', ax=self.ax)
        self.ax.set_xticklabels(dataframe.index, rotation=0)
        self.fig.tight_layout()
        self.draw()