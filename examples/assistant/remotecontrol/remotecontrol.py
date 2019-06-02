import sys
from PyQt5 import QtCore, QtGui, QtWidgets

from remotecontrol_ui import Ui_RemoteControlClass


class RemoteControl(QtWidgets.QMainWindow):
    def __init__(self, parent=None, flags=QtCore.Qt.Widget):
        super(RemoteControl, self).__init__(parent, flags)
        self.ui = Ui_RemoteControlClass()
        self.ui.setupUi(self)
        self.ui.indexLineEdit.returnPressed.connect(self.on_indexButton_clicked)
        self.ui.identifierLineEdit.returnPressed.connect(
            self.on_identifierButton_clicked
        )
        self.ui.urlLineEdit.returnPressed.connect(self.on_urlButton_clicked)

        rc = "qthelp://org.qt-project.qtdoc."
        rc += "{}{}{}".format(
            QtCore.QT_VERSION >> 16,
            (QtCore.QT_VERSION >> 8) & 0xFF,
            QtCore.QT_VERSION & 0xFF,
        )
        rc += "/qtdoc/index.html"
        self.ui.startUrlLineEdit.setText(rc)

        self.process = QtCore.QProcess(self)
        self.process.finished.connect(self.helpViewerClosed)

    def __del__(self):
        if self.process.state() == QtCore.QProcess.Running:
            self.process.terminate()
            self.process.waitForFinished(3000)

    @QtCore.pyqtSlot()
    def on_launchButton_clicked(self):
        if self.process.state() == QtCore.QProcess.Running:
            return

        app = (
            QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.BinariesPath)
            + QtCore.QDir.separator()
        )
        if sys.platform != "darwin":
            app += "assistant"
        else:
            app += "Assistant.app/Contents/MacOS/Assistant"

        self.ui.contentsCheckBox.setChecked(True)
        self.ui.indexCheckBox.setChecked(True)
        self.ui.bookmarksCheckBox.setChecked(True)

        args = ["-enableRemoteControl"]
        self.process.start(app, args)
        if not self.process.waitForStarted():
            QtWidgets.QMessageBox.critical(
                self,
                self.tr("Remote Control"),
                self.tr("Could not start Qt Assistant from %s." % (app,)),
            )
            return

        if self.ui.startUrlLineEdit.text():
            self.sendCommand("SetSource " + self.ui.startUrlLineEdit.text())

        self.ui.launchButton.setEnabled(False)
        self.ui.startUrlLineEdit.setEnabled(False)
        self.ui.actionGroupBox.setEnabled(True)

    @QtCore.pyqtSlot()
    def on_actionQuit_triggered(self):
        self.close()

    @QtCore.pyqtSlot()
    def on_indexButton_clicked(self):
        self.sendCommand("ActivateKeyword " + self.ui.indexLineEdit.text())

    @QtCore.pyqtSlot()
    def on_identifierButton_clicked(self):
        self.sendCommand(
            "ActivateIdentifier " + self.ui.identifierLineEdit.text()
        )

    @QtCore.pyqtSlot()
    def on_urlButton_clicked(self):
        self.sendCommand("SetSource " + self.ui.urlLineEdit.text())

    @QtCore.pyqtSlot()
    def on_syncContentsButton_clicked(self):
        self.sendCommand("SyncContents")

    @QtCore.pyqtSlot(bool)
    def on_contentsCheckBox_toggled(self, checked):
        self.sendCommand("Show Contents" if checked else "Hide Contents")

    @QtCore.pyqtSlot(bool)
    def on_indexCheckBox_toggled(self, checked):
        self.sendCommand("Show Index" if checked else "Hide Index")

    @QtCore.pyqtSlot(bool)
    def on_bookmarksCheckBox_toggled(self, checked):
        self.sendCommand("Show Bookmarks" if checked else "Hide Bookmarks")

    @QtCore.pyqtSlot()
    def helpViewerClosed(self):
        self.ui.launchButton.setEnabled(True)
        self.ui.startUrlLineEdit.setEnabled(True)
        self.ui.actionGroupBox.setEnabled(False)

    @QtCore.pyqtSlot(str)
    def sendCommand(self, cmd):
        if self.process.state() != QtCore.QProcess.Running:
            return
        self.process.write((cmd + "\n").encode())


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = RemoteControl()
    w.show()
    sys.exit(app.exec_())
