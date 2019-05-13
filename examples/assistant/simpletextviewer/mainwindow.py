from PyQt5 import QtCore, QtGui, QtWidgets

from assistant import Assistant
from textedit import TextEdit
from findfiledialog import FindFileDialog


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.assistant = Assistant()
        self.textViewer = TextEdit()
        self.textViewer.setContents(
            QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.ExamplesPath)
            + "/assistant/simpletextviewer/documentation/intro.html"
        )
        self.setCentralWidget(self.textViewer)

        self._createActions()
        self._createMenus()

        self.setWindowTitle(self.tr("Simple Text Viewer"))
        self.resize(750, 400)

    def _showDocumentation(self):
        self.assistant.showDocumentation("index.html")

    @QtCore.pyqtSlot()
    def _about(self):
        QtWidgets.QMessageBox.about(
            self,
            self.tr("About Simple Text Viewer"),
            self.tr(
                "This example demonstrates how to use\n"
                "Qt Assistant as help system for your\n"
                "own application."
            ),
        )

    @QtCore.pyqtSlot()
    def _open(self):
        dialog = FindFileDialog(self.textViewer, self.assistant)
        dialog.exec_()

    def _createActions(self):
        self.assistantAct = QtWidgets.QAction(
            self.tr("Help Contents"),
            self,
            shortcut=QtGui.QKeySequence.HelpContents,
            triggered=self._showDocumentation,
        )
        self.openAct = QtWidgets.QAction(
            self.tr("&Open..."),
            self,
            shortcut=QtGui.QKeySequence.Open,
            triggered=self._open,
        )
        self.clearAct = QtWidgets.QAction(
            self.tr("&Clear"),
            self,
            shortcut=self.tr("Ctrl+C"),
            triggered=self.textViewer.clear,
        )
        self.exitAct = QtWidgets.QAction(
            self.tr("E&xit"),
            self,
            shortcut=QtGui.QKeySequence.Quit,
            triggered=self.close,
        )
        self.aboutAct = QtWidgets.QAction(
            self.tr("&About"), self, triggered=self._about
        )
        self.aboutQtAct = QtWidgets.QAction(
            self.tr("About &Qt"), self, triggered=QtWidgets.QApplication.aboutQt
        )

    def _createMenus(self):
        fileMenu = QtWidgets.QMenu(self.tr("&File"), self)
        fileMenu.addAction(self.openAct)
        fileMenu.addAction(self.clearAct)
        fileMenu.addSeparator()
        fileMenu.addAction(self.exitAct)

        helpMenu = QtWidgets.QMenu(self.tr("&Help"), self)
        helpMenu.addAction(self.assistantAct)
        helpMenu.addSeparator()
        helpMenu.addAction(self.aboutAct)
        helpMenu.addAction(self.aboutQtAct)

        self.menuBar().addMenu(fileMenu)
        self.menuBar().addMenu(helpMenu)
