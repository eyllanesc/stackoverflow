from PyQt5 import QtCore, QtGui, QtWidgets

from droparea import DropArea


class DropSiteWindow(QtWidgets.QWidget):
    def __init__(self):
        super(DropSiteWindow, self).__init__()
        self.abstractLabel = QtWidgets.QLabel(
            self.tr(
                "This example accepts drags from other "
                "applications and displays the MIME types "
                "provided by the drag object."
            )
        )
        self.abstractLabel.setWordWrap(True)
        self.abstractLabel.adjustSize()

        self.dropArea = DropArea()
        self.dropArea.changed.connect(self.updateFormatsTable)

        labels = [self.tr("Format"), self.tr("Content")]

        self.formatsTable = QtWidgets.QTableWidget()
        self.formatsTable.setColumnCount(2)
        self.formatsTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers
        )
        self.formatsTable.setHorizontalHeaderLabels(labels)
        self.formatsTable.horizontalHeader().setStretchLastSection(True)

        self.clearButton = QtWidgets.QPushButton(self.tr("Clear"))
        self.quitButton = QtWidgets.QPushButton(self.tr("Quit"))

        self.buttonBox = QtWidgets.QDialogButtonBox()
        self.buttonBox.addButton(
            self.clearButton, QtWidgets.QDialogButtonBox.ActionRole
        )
        self.buttonBox.addButton(
            self.quitButton, QtWidgets.QDialogButtonBox.RejectRole
        )

        self.quitButton.clicked.connect(self.close)
        self.clearButton.clicked.connect(self.dropArea.clear)

        mainLayout = QtWidgets.QVBoxLayout(self)
        mainLayout.addWidget(self.abstractLabel)
        mainLayout.addWidget(self.dropArea)
        mainLayout.addWidget(self.formatsTable)
        mainLayout.addWidget(self.buttonBox)

        self.setWindowTitle(self.tr("Drop Site"))
        self.setMinimumSize(350, 500)

    @QtCore.pyqtSlot(QtCore.QMimeData)
    def updateFormatsTable(self, mimeData):
        self.formatsTable.setRowCount(0)
        if mimeData is None:
            return

        for _format in mimeData.formats():
            formatItem = QtWidgets.QTableWidgetItem(_format)
            formatItem.setFlags(QtCore.Qt.ItemIsEnabled)
            formatItem.setTextAlignment(
                QtCore.Qt.AlignTop | QtCore.Qt.AlignLeft
            )

            text = ""
            if _format == "text/plain":
                text = " ".join(mimeData.text().strip().split())
            elif _format == "text/html":
                text = " ".join(mimeData.html().strip().split())
            elif _format == "text/uri-list":
                urlList = mimeData.urls()
                for url in urlList:
                    text += url.toString() + " "
            else:
                data = mimeData.data(_format)
                text = " ".join(["{:02X}".format(x) for x in data.data()])

            row = self.formatsTable.rowCount()
            self.formatsTable.insertRow(row)
            self.formatsTable.setItem(
                row, 0, formatItem
            )
            self.formatsTable.setItem(row, 1, QtWidgets.QTableWidgetItem(text))

        self.formatsTable.resizeColumnToContents(0)
