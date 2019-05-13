from PyQt5 import QtCore, QtWidgets

from blurpicker import BlurPicker


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)

    blurPicker = BlurPicker()
    blurPicker.setWindowTitle(
        QtCore.QT_TRANSLATE_NOOP(QtWidgets.QGraphicsView, "Application Picker")
    )

    blurPicker.setFixedSize(400, 300)
    blurPicker.show()

    sys.exit(app.exec_())
