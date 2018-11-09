import csv
import sys
from PyQt4.QtCore import QPoint, Qt, QString
from PyQt4.QtGui import QApplication, QCheckBox, QDialogButtonBox, QMenu, QTableWidget, QWidgetAction, QTableWidgetItem


class FilterTableWidget(QTableWidget):
    def __init__(self, parent=None):
        super(FilterTableWidget, self).__init__(parent=parent)
        self.horizontalHeader = self.horizontalHeader()
        self.horizontalHeader.sectionClicked.connect(self.on_view_horizontalHeader_sectionClicked)
        self.keywords = dict([(i, []) for i in range(self.columnCount())])
        self.checkBoxs = []
        self.col = None

    def on_view_horizontalHeader_sectionClicked(self, index):
        self.menu = QMenu(self)
        self.col = index

        data_unique = []

        self.checkBoxs = []

        self.checkBoxSelect = QCheckBox("Select all", self.menu)
        checkableAction = QWidgetAction(self.menu)
        checkableAction.setDefaultWidget(self.checkBoxSelect)
        self.menu.addAction(checkableAction)
        self.checkBoxSelect.setChecked(True)
        self.checkBoxSelect.stateChanged.connect(self.onSelect)

        for i in range(self.rowCount()):
            if not self.isRowHidden(i):
                item = self.item(i, index)
                if item.text() not in data_unique:
                    data_unique.append(item.text())
                    checkBox = QCheckBox(item.text(), self.menu)
                    checkBox.setChecked(True)
                    checkBox.stateChanged.connect(self.onClickedElement)
                    checkableAction = QWidgetAction(self.menu)
                    checkableAction.setDefaultWidget(checkBox)
                    self.menu.addAction(checkableAction)
                    self.checkBoxs.append(checkBox)

        btn = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel,
                                     Qt.Horizontal, self.menu)
        btn.accepted.connect(self.menuClose)
        btn.rejected.connect(self.menu.close)
        checkableAction =QWidgetAction(self.menu)
        checkableAction.setDefaultWidget(btn)
        self.menu.addAction(checkableAction)

        headerPos = self.mapToGlobal(self.horizontalHeader.pos())

        posY = headerPos.y() + self.horizontalHeader.height()
        posX = headerPos.x() + self.horizontalHeader.sectionPosition(index)
        self.menu.exec_(QPoint(posX, posY))

    def onClickedElement(self):
    	if self.checkBoxSelect.isChecked(): 
    		self.checkBoxSelect.setChecked(False)
    		

    def onSelect(self, state):
        for checkbox in self.checkBoxs:
            checkbox.setChecked(Qt.Checked == state)

    def menuClose(self):
        self.keywords[self.col] = []
        for element in self.checkBoxs:
            if element.isChecked():
                self.keywords[self.col].append(element.text())
        self.filterdata()
        self.menu.close()

    def filterdata(self):

        columnsShow = dict([(i, True) for i in range(self.rowCount())])

        for i in range(self.rowCount()):
            for j in range(self.columnCount()):
                item = self.item(i, j)
                if j in self.keywords:
	                if self.keywords[j]:
	                    if item.text() not in self.keywords[j]:
	                        columnsShow[i] = False
        for key, value in columnsShow.iteritems():
            self.setRowHidden(key, not value)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = FilterTableWidget()
    with open("../Rts.csv", "rb") as inpfil:
        reader = csv.reader(inpfil, delimiter=',')
        csheader = reader.next()
        ncol = len(csheader)
        data = list(reader)
        row_count = len(data)

        w.setRowCount(row_count)
        w.setColumnCount(ncol)
        w.setHorizontalHeaderLabels(QString('%s' % ', '.join(map(str, csheader))).split(","))

        for ii in range(0, row_count):
            mainins = data[ii]
            for var in range(0, ncol):
                w.setItem(ii, var, QTableWidgetItem(mainins[var]))
    w.show()
    sys.exit(app.exec_())