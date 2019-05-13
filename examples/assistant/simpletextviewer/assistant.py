import platform

from PyQt5 import QtCore, QtWidgets


class Assistant:
    def __init__(self, parent=None):
        self.proc = None

    def showDocumentation(self, page):
        if not self.startAssistant():
            return
        ba = (
            "SetSource qthelp://org.qt-project.examples.simpletextviewer/doc/"
            + page
            + "\n"
        )
        self.proc.write(ba.encode())

    def startAssistant(self):
        if self.proc is None:
            self.proc = QtCore.QProcess()
        if self.proc.state() != QtCore.QProcess.Running:
            app = (
                QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.BinariesPath)
                + QtCore.QDir.separator()
            )
            if platform.system() != "Darwin":
                app += "assistant"
            else:
                app += "Assistant.app/Contents/MacOS/Assistant"

            args = [
                "-collectionFile",
                QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.ExamplesPath)
                + "/assistant/simpletextviewer/documentation/simpletextviewer.qhc",
                "-enableRemoteControl",
            ]
            self.proc.start(app, args)
            if not self.proc.waitForStarted():
                QtWidgets.QMessageBox.critical(
                    None,
                    "Simple Text Viewer",
                    "Unable to launch Qt Assistant (%s)" % (app,),
                )
                return False
        return True
