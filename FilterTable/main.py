import csv

import sys
from PyQt4 import QtGui
from PyQt4 import uic
from PyQt4.QtCore import QString
from PyQt4.QtGui import QTableWidgetItem

filter_class = uic.loadUiType("filter.ui")[0]


class Filter_window(QtGui.QWidget, filter_class):
    def __init__(self, parent=None, *args, **kwargs):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.loadAll()

    def loadAll(self):

        with open("Rts.csv", "rb") as inpfil:

            reader = csv.reader(inpfil, delimiter=',')
            csheader = reader.next()
            ncol = len(csheader)
            data = list(reader)
            row_count = len(data)

            self.filterall.setRowCount(row_count)
            self.filterall.setColumnCount(ncol)
            self.filterall.setHorizontalHeaderLabels(QString('%s' % ', '.join(map(str, csheader))).split(","))
            for ii in range(0, row_count):
                print data[ii]
                mainins = data[ii]
                print mainins
                for var in range(0, ncol):
                    print mainins[var], "\n"
                    self.filterall.setItem(ii, var, QTableWidgetItem(mainins[var]))


if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    filterwin = Filter_window()
    filterwin.show()
    sys.exit(app.exec_())
