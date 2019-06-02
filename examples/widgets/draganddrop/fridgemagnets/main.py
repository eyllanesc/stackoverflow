from PyQt5 import QtCore, QtWidgets

from dragwidget import DragWidget

if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    if hasattr(QtWidgets.QApplication, "setNavigationMode"):
        QtWidgets.QApplication.setNavigationMode(
            QtCore.Qt.NavigationModeCursorAuto
        )
    window = DragWidget()

    smallScreen = "-small-screen" in QtWidgets.QApplication.arguments()
    if smallScreen:
        window.showFullScreen()
    else:
        window.show()

    sys.exit(app.exec_())
