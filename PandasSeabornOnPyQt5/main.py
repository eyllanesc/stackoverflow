import sys

# import gtk
# gtk.set_interactive(False)
import matplotlib

matplotlib.use('Qt5Agg', force=True)

import matplotlib.pyplot as plt
plt.switch_backend('Qt5Agg')

import pandas as pd
import seaborn as sns



from PyQt5 import QtCore, QtWidgets


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

        # sns.pairplot(data, ax= self.axes, x_vars=['TV', 'Radio', 'Newspaper'],
        #  y_vars='Sales', size=7, aspect=0.7, kind='reg')

        axes1 = self.fig.add_subplot(2, 3, 1)
        axes2 = self.fig.add_subplot(2, 3, 2)
        axes3 = self.fig.add_subplot(2, 3, 3)

        # https://stackoverflow.com/questions/17329292/matplotlib-set-shared-axis

        axes1.get_shared_y_axes().join(axes1, axes2)
        axes1.get_shared_y_axes().join(axes1, axes3)

        data = pd.read_csv('Advertising.csv')

        sns.regplot(ax=axes1, x=data['TV'], y=data['Sales'])
        sns.regplot(ax=axes2, x=data['Radio'], y=data['Sales'])
        sns.regplot(ax=axes3, x=data['Newspaper'], y=data['Sales'])

        axes4 = self.fig.add_subplot(2, 1, 2)

        df = pd.DataFrame({'a': 10, 'b': 20, 'c': 30}, index=[0])
        sns.set(color_codes=True)

        df.plot(kind='bar', ax=axes4)


class ApplicationWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QMainWindow.__init__(self, parent=parent)
        self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.setWindowTitle("Plot with Pandas and Seaborn")

        self.main_widget = QtWidgets.QWidget(self)

        l = QtWidgets.QVBoxLayout(self.main_widget)
        sc = MyMplCanvas(self.main_widget, width=5, height=4, dpi=100)
        l.addWidget(sc)

        self.main_widget.setFocus()
        self.setCentralWidget(self.main_widget)


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    w = ApplicationWindow()
    w.showMaximized()
    sys.exit(app.exec_())
