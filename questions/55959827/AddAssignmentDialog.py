from PyQt5 import QtCore, QtGui, QtWidgets

from AddAssignmentDialog_ui import Ui_AddAssignmentDialog


class AddAssignmentDialog(QtWidgets.QDialog, Ui_AddAssignmentDialog):
    def __init__(self, parent=None):
        super(AddAssignmentDialog, self).__init__(parent)
        self.setupUi(self)
        self.filename = ""

        self.browseButton.clicked.connect(self.browserFile)
        self.submitButton.clicked.connect(self.accept)

    @QtCore.pyqtSlot()
    def browserFile(self):
        self.filename, _ = QtWidgets.QFileDialog.getOpenFileName(
            None,
            "Open file",
            QtCore.QStandardPaths.writableLocation(QtCore.QStandardPaths.DesktopLocation),
            "",
            "",
        )
        if self.filename:
            finfo = QtCore.QFileInfo(self.filename)
            self.uploadFileNameLine.setText(finfo.fileName())

    def get_assignment(self):
        assignmentName = self.assignmentNameLine.text()
        assignmentDue = self.dueLine.text()
        description = self.descriptionText.toPlainText()
        return {"name": assignmentName, "due": assignmentDue, "description": description}


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = AddAssignmentDialog()
    w.show()
    sys.exit(app.exec_())
