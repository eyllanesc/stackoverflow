from Qt import QtCore, QtGui, QtWidgets


class TextEdit(QtWidgets.QTextEdit):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.srcUrl = QtCore.QUrl()
        self.setReadOnly(True)

    def setContents(self, fileName):
        fi = QtCore.QFileInfo(fileName)
        self.srcUrl = QtCore.QUrl.fromLocalFile(fi.absoluteFilePath())
        file = QtCore.QFile(fileName)
        if file.open(QtCore.QIODevice.ReadOnly):
            data = file.readAll().data().decode()
            if fileName.endswith(".html"):
                self.setHtml(data)
            else:
                self.setPlainText(data)

    def loadResource(self, _type, name):
        if _type == QtGui.QTextDocument.ImageResource:
            file = QtCore.QFile(self.srcUrl.resolved(name).toLocalFile())
            if file.open(QtCore.QIODevice.ReadOnly):
                return file.readAll()
        return super().loadResource(_type, name)
