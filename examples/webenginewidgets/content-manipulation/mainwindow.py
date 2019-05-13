from PyQt5 import QtCore, QtWidgets, QtWebEngineWidgets

import jquery_rc


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, url):
        super().__init__()
        self.setAttribute(QtCore.Qt.WA_DeleteOnClose, True)
        self.progress = 0

        file = QtCore.QFile()
        file.setFileName(":/jquery.min.js")
        file.open(QtCore.QIODevice.ReadOnly)
        self.jQuery = file.readAll().data().decode()
        self.jQuery += "\nvar qt = { 'jQuery': jQuery.noConflict(true) };"
        file.close()

        self.view = QtWebEngineWidgets.QWebEngineView(self)
        self.view.load(url)
        self.view.loadFinished.connect(self.adjustLocation)
        self.view.titleChanged.connect(self.adjustTitle)
        self.view.loadProgress.connect(self.setProgress)
        self.view.loadFinished.connect(self.finishLoading)

        self.locationEdit = QtWidgets.QLineEdit()
        self.locationEdit.setSizePolicy(
            QtWidgets.QSizePolicy.Expanding,
            self.locationEdit.sizePolicy().verticalPolicy(),
        )
        self.locationEdit.returnPressed.connect(self.changeLocation)

        toolBar = self.addToolBar(self.tr("Navigation"))
        toolBar.addAction(
            self.view.pageAction(QtWebEngineWidgets.QWebEnginePage.Back)
        )
        toolBar.addAction(
            self.view.pageAction(QtWebEngineWidgets.QWebEnginePage.Forward)
        )
        toolBar.addAction(
            self.view.pageAction(QtWebEngineWidgets.QWebEnginePage.Reload)
        )
        toolBar.addAction(
            self.view.pageAction(QtWebEngineWidgets.QWebEnginePage.Stop)
        )
        toolBar.addWidget(self.locationEdit)

        viewMenu = self.menuBar().addMenu(self.tr("&View"))
        viewSourceAction = QtWidgets.QAction(self.tr("Page Source"), self)
        viewSourceAction.triggered.connect(self.viewSource)
        viewMenu.addAction(viewSourceAction)

        effectMenu = self.menuBar().addMenu(self.tr("&Effect"))
        effectMenu.addAction(
            self.tr("Highlight all links"), self.highlightAllLinks
        )

        self.rotateAction = QtWidgets.QAction(self)
        self.rotateAction.setIcon(
            self.style().standardIcon(
                QtWidgets.QStyle.SP_FileDialogDetailedView
            )
        )
        self.rotateAction.setCheckable(True)
        self.rotateAction.setText(self.tr("Turn images upside down"))
        self.rotateAction.toggled.connect(self.rotateImages)
        effectMenu.addAction(self.rotateAction)

        toolsMenu = self.menuBar().addMenu(self.tr("&Tools"))
        toolsMenu.addAction(self.tr("Remove GIF image"), self.removeGifImages)
        toolsMenu.addAction(
            self.tr("Remove all inline frames"), self.removeInlineFrames
        )
        toolsMenu.addAction(
            self.tr("Remove all object elements"), self.removeObjectElements
        )
        toolsMenu.addAction(
            self.tr("Remove all embedded elements"), self.removeEmbeddedElements
        )

        self.setCentralWidget(self.view)

    @QtCore.pyqtSlot()
    def adjustLocation(self):
        self.locationEdit.setText(self.view.url().toString())

    @QtCore.pyqtSlot()
    def changeLocation(self):
        url = QtCore.QUrl.fromUserInput(self.locationEdit.text())
        self.view.load(url)
        self.view.setFocus()

    @QtCore.pyqtSlot()
    def adjustTitle(self):
        if self.progress <= 0 or self.progress >= 100:
            self.setWindowTitle(self.view.title())
        else:
            self.setWindowTitle(
                "{} ({}%)".format(self.view.title(), self.progress)
            )

    @QtCore.pyqtSlot(int)
    def setProgress(self, p):
        self.progress = p
        self.adjustTitle()

    @QtCore.pyqtSlot()
    def finishLoading(self):
        self.progress = 100
        self.adjustTitle()
        self.view.page().runJavaScript(self.jQuery)
        self.rotateImages(self.rotateAction.isChecked())

    @QtCore.pyqtSlot()
    def viewSource(self):
        self.textEdit = QtWidgets.QTextEdit()
        self.textEdit.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.textEdit.adjustSize()
        self.textEdit.move(
            self.geometry().center() - self.textEdit.rect().center()
        )
        self.textEdit.show()
        self.view.page().toHtml(self.textEdit.setPlainText)

    @QtCore.pyqtSlot()
    def highlightAllLinks(self):
        code = "qt.jQuery('a').each( function () { qt.jQuery(this).css('background-color', 'yellow') } )"
        self.view.page().runJavaScript(code)

    @QtCore.pyqtSlot(bool)
    def rotateImages(self, invert):
        code = ""
        if invert:
            code = "qt.jQuery('img').each( function () { qt.jQuery(this).css('transition', 'transform 2s'); qt.jQuery(this).css('transform', 'rotate(180deg)') } )"
        else:
            code = "qt.jQuery('img').each( function () { qt.jQuery(this).css('transition', 'transform 2s'); qt.jQuery(this).css('transform', 'rotate(0deg)') } )"
        self.view.page().runJavaScript(code)

    @QtCore.pyqtSlot()
    def removeGifImages(self):
        code = "qt.jQuery('[src*=gif]').remove()"
        self.view.page().runJavaScript(code)

    @QtCore.pyqtSlot()
    def removeInlineFrames(self):
        code = "qt.jQuery('iframe').remove()"
        self.view.page().runJavaScript(code)

    @QtCore.pyqtSlot()
    def removeObjectElements(self):
        code = "qt.jQuery('object').remove()"
        self.view.page().runJavaScript(code)

    @QtCore.pyqtSlot()
    def removeEmbeddedElements(self):
        code = "qt.jQuery('embed').remove()"
        self.view.page().runJavaScript(code)
