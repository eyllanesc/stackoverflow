from PyQt5 import QtCore, QtGui, QtWidgets

from AssignmentSectionWindow_ui import Ui_AssignmentSectionWindow
from AddAssignmentDialog import AddAssignmentDialog


class AssignmentSectionWindow(QtWidgets.QMainWindow, Ui_AssignmentSectionWindow):
    def __init__(self, parent=None):
        super(AssignmentSectionWindow, self).__init__(parent)
        self.setupUi(self)
        self.addAssignmentButton.clicked.connect(self.addAssignment)
        self.assignmentLabel.setText("Assignments of xxx")

    @QtCore.pyqtSlot()
    def addAssignment(self):
        w = AddAssignmentDialog()
        if w.exec_() == QtWidgets.QDialog.Accepted:
            data = w.get_assignment()
            print(data)


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = AssignmentSectionWindow()
    w.show()
    sys.exit(app.exec_())
