from PyQt5 import QtCore


class Core(QtCore.QObject):
    sendText = QtCore.pyqtSignal(str)

    def __init__(self, dialog, parent=None):
        super(Core, self).__init__(parent)
        self.m_dialog = dialog
        dialog.sendText.connect(self.sendText)

    @QtCore.pyqtSlot()
    def receiveText(self, text):
        self.m_dialog.displayMessage(
            self.m_dialog.tr("Received message: %s" % (text,))
        )
