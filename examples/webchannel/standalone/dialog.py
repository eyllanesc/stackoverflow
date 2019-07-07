from PyQt5 import QtCore, QtWidgets

from dialog_ui import Ui_Dialog


class Dialog(QtWidgets.QDialog):
    sendText = QtCore.pyqtSignal(str)

    def __init__(self, parent=None):
        super(Dialog, self).__init__(parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.ui.send.clicked.connect(self.clicked)

    def displayMessage(self, message):
        self.ui.output.appendPlainText(message)

    @QtCore.pyqtSlot()
    def clicked(self):
        text = self.ui.input.text()
        if not text:
            return

        self.sendText.emit(text)
        self.displayMessage(self.tr("Sent message: %s" % (text,)))
        self.ui.input.clear()
