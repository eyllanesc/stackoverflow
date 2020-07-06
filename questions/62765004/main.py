import os
from PyQt5 import QtCore, QtGui, QtWidgets, QtHelp


CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))


class HelpBrowser(QtWidgets.QTextBrowser):
    def __init__(self, helpEngine, parent=None):
        super().__init__(parent)
        self.helpEngine = helpEngine

    def loadResource(self, _type, name):
        if name.scheme() == "qthelp":
            return self.helpEngine.fileData(name)
        else:
            return super().loadResource(_type, name)


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.createHelpWindow()
        self.createActions()
        self.createMenus()
        self.createConnections()

        self.resize(640, 480)

    def createHelpWindow(self):
        self.helpEngine = QtHelp.QHelpEngine(
            os.path.join(CURRENT_DIR, "documentation", "qgraphicshelpexample.qhc")
        )
        self.helpEngine.setupData()

        tWidget = QtWidgets.QTabWidget()
        tWidget.setMaximumWidth(200)
        tWidget.addTab(self.helpEngine.contentWidget(), "Contents")
        tWidget.addTab(self.helpEngine.indexWidget(), "Index")

        textViewer = HelpBrowser(self.helpEngine)
        textViewer.setSource(
            QtCore.QUrl("qthelp://walletfox.qt.helpexample/doc/index.html")
        )

        self.helpEngine.contentWidget().linkActivated.connect(textViewer.setSource)

        self.helpEngine.indexWidget().linkActivated.connect(textViewer.setSource)

        horizSplitter = QtWidgets.QSplitter(QtCore.Qt.Horizontal)
        horizSplitter.insertWidget(0, tWidget)
        horizSplitter.insertWidget(1, textViewer)
        horizSplitter.hide()

        self.helpWindow = QtWidgets.QDockWidget(self.tr("Help"), self)
        self.helpWindow.setWidget(horizSplitter)
        self.helpWindow.hide()
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.helpWindow)

        self.scene = QtWidgets.QGraphicsScene()
        self.view = QtWidgets.QGraphicsView(self.scene)
        self.setCentralWidget(self.view)

    def createActions(self):

        self.insertEllipseAction = QtWidgets.QAction(self.tr("Insert &Ellipse"), self)
        self.insertEllipseAction.setIcon(QtGui.QIcon(":/icons/ellipse.png"))

        self.insertRectangleAction = QtWidgets.QAction(
            self.tr("Insert &Rectangle"), self
        )
        self.insertRectangleAction.setIcon(QtGui.QIcon(":/icons/rectangle.png"))

        self.helpAction = QtWidgets.QAction(self.tr("Help Contents..."), self)
        self.helpAction.setShortcut(QtGui.QKeySequence.HelpContents)

        self.aboutAction = QtWidgets.QAction(self.tr("&About"), self)

    def createMenus(self):
        self.itemMenu = QtWidgets.QMenu(self.tr("&Item"), self)
        self.itemMenu.addAction(self.insertEllipseAction)
        self.itemMenu.addAction(self.insertRectangleAction)

        self.helpMenu = QtWidgets.QMenu(self.tr("&Help"), self)
        self.helpMenu.addAction(self.helpAction)
        self.helpMenu.addAction(self.aboutAction)

        self.menuBar().addMenu(self.itemMenu)
        self.menuBar().addMenu(self.helpMenu)

    def insertItem(self):
        action = self.sender()
        if isinstance(action, QtWidgets.QAction):
            itemToAdd = None
            mPen = QtGui.QPen(QtCore.Qt.black, 3, QtCore.Qt.SolidLine)
            eBrush = QtGui.QBrush(QtGui.QColor("#FF7F50"))
            rBrush = QtGui.QBrush(QtGui.QColor("#CC0000"))
            if action.iconText() == "Insert Ellipse":
                itemToAdd = self.scene.addEllipse(0, 0, 150, 75, mPen, eBrush)
            elif action.iconText() == "Insert Rectangle":
                itemToAdd = self.scene.addRect(0, 0, 100, 100, mPen, rBrush)
            if itemToAdd is not None:
                itemToAdd.setFlags(
                    QtWidgets.QGraphicsItem.ItemIsSelectable
                    | QtWidgets.QGraphicsItem.ItemIsMovable
                )

    def about(self):
        QtWidgets.QMessageBox.about(
            self,
            self.tr("About QGraphicsScene Help Example"),
            self.tr(
                "This example demonstrates how to implement\n"
                "help for a Qt application."
            ),
        )

    def createConnections(self):
        self.insertEllipseAction.triggered.connect(self.insertItem)
        self.insertRectangleAction.triggered.connect(self.insertItem)
        self.helpAction.triggered.connect(self.helpWindow.show)
        self.aboutAction.triggered.connect(self.about)

    def keyPressEvent(self, event):
        pass


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
