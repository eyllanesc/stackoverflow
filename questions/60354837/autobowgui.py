import configparser
from PyQt5 import QtCore, QtGui, QtWidgets

from autobowgui_ui import Ui_Dialog


class AutoBowGui(QtWidgets.QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super(AutoBowGui, self).__init__(parent)
        self.setupUi(self)
        self.setFixedHeight(self.sizeHint().height())
        self.pushButton.clicked.connect(self.save_settings)

        self.config = configparser.ConfigParser()
        self.config.read("Config.ini")

        self.lineEdit.setText(str(self.config.get("AutoBow", "drawdelay")))
        self.lineEdit_2.setText(str(self.config.get("AutoBow", "start1")))
        self.lineEdit_3.setText(str(self.config.get("AutoBow", "start2")))
        self.lineEdit_4.setText(str(self.config.get("AutoBow", "pause1")))
        self.lineEdit_5.setText(str(self.config.get("AutoBow", "pause2")))

    @QtCore.pyqtSlot()
    def save_settings(self):
        self.config.set("AutoBow", "drawdelay", self.lineEdit.text())
        self.config.set("AutoBow", "start1", self.lineEdit_2.text())
        self.config.set("AutoBow", "start2", self.lineEdit_3.text())
        self.config.set("AutoBow", "pause1", self.lineEdit_4.text())
        self.config.set("AutoBow", "pause2", self.lineEdit_5.text())
        with open("Config.ini", "w") as configfile:
            self.config.write(configfile)
        QtCore.QTimer.singleShot(500, self.accept)


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    w = AutoBowGui()
    w.show()
    sys.exit(app.exec_())
