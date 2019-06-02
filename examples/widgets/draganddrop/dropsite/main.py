from PyQt5 import QtWidgets

from dropsitewindow import DropSiteWindow

if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    window = DropSiteWindow()
    window.show()
    sys.exit(app.exec_())
