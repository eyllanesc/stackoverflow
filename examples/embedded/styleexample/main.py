from PyQt5 import QtWidgets

from stylewidget import StyleWidget


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = StyleWidget()
    w.show()
    sys.exit(app.exec_())