from PyQt5 import QtCore, QtGui, QtWidgets


class DropArea(QtWidgets.QLabel):
    changed = QtCore.pyqtSignal(QtCore.QMimeData)

    def __init__(self, parent=None):
        super(DropArea, self).__init__(parent)
        self.setMinimumSize(200, 200)
        self.setFrameStyle(
            QtWidgets.QFrame.Sunken | QtWidgets.QFrame.StyledPanel
        )
        self.setAlignment(QtCore.Qt.AlignCenter)
        self.setAcceptDrops(True)
        self.setAutoFillBackground(True)
        self.clear()

    def dragEnterEvent(self, event):
        self.setText(self.tr("<drop content>"))
        self.setBackgroundRole(QtGui.QPalette.Highlight)

        event.acceptProposedAction()
        self.changed.emit(event.mimeData())

    def dragMoveEvent(self, event):
        event.acceptProposedAction()

    def dropEvent(self, event):
        mimeData = event.mimeData()
        if mimeData.hasImage():
            self.setPixmap(mimeData.imageData())
        elif mimeData.hasHtml():
            self.setText(mimeData.html())
            self.setTextFormat(QtCore.Qt.RichText)
        elif mimeData.hasText():
            self.setText(mimeData.text())
            self.setTextFormat(QtCore.Qt.PlainText)
        elif mimeData.hasUrls():
            urlList = mimeData.urls()
            text = ""
            for i, url in enumerate(urlList):
                if i >= 32:
                    break
                else:
                    text += url.path() + "\n"
            self.setText(text)
        else:
            self.setText(self.tr("Cannot display data"))

        self.setBackgroundRole(QtGui.QPalette.Dark)
        event.acceptProposedAction()

    def dragLeaveEvent(self, event):
        self.clear()
        event.accept()

    @QtCore.pyqtSlot()
    def clear(self):
        self.setText(self.tr("<drop content>"))
        self.setBackgroundRole(QtGui.QPalette.Dark)
        self.changed.emit(None)
