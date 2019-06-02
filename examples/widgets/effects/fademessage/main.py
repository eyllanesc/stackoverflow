from PyQt5 import QtCore, QtWidgets

from fademessage import FadeMessage

if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)

    widget = FadeMessage()
    widget.setWindowTitle(
        QtCore.QT_TRANSLATE_NOOP(
            QtWidgets.QGraphicsView, "Popup Message with Effect"
        )
    )
    widget.setFixedSize(400, 600)
    widget.show()

    sys.exit(app.exec_())
