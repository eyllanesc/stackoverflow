import os

from PyQt5 import QtWidgets


def main(args):
    app = QtWidgets.QApplication(args)

    w = QtWidgets.QLineEdit()
    w.show()

    ret = app.exec_()
    return ret


if __name__ == "__main__":
    import sys

    sys.exit(main(sys.argv))