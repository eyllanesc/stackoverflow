import os.path

from PyQt5.uic import loadUi
from PyQt5.QtWidgets import QApplication


def main():
    app = QApplication([])
    base_dir = os.path.dirname(__file__)
    ui_filename = os.path.join(base_dir, "ui", "main.ui")
    w = loadUi(ui_filename)
    w.show()

    app.exec_()


if __name__ == "__main__":
    main()
