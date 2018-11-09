import os
import sys
from PyQt5 import QtCore, QtGui, QtWidgets

dir_path = os.path.dirname(os.path.realpath(__file__))

positions_button_KA = [(330, 70, 10, 20),(270, 110, 10, 20),(300, 110, 10, 20),(360, 110, 10, 20),(330, 150, 10, 20),
                       (180, 190, 10, 20),(240, 190, 10, 20),(300, 190, 10, 20),(360, 190, 10, 20),(210, 230, 10, 20),
                       (270, 230, 10, 20),(330, 230, 10, 20),(180, 270, 10, 20),(240, 270, 10, 20),(270, 270, 10, 20),
                       (300, 270, 10, 20),(360, 270, 10, 20),(210, 310, 10, 20),(330, 310, 10, 20),(180, 350, 10, 20),
                       (240, 350, 10, 20),(300, 350, 10, 20),(360, 350, 10, 20),(210, 390, 10, 20),(270, 390, 10, 20),
                       (330, 390, 10, 20),(180, 430, 10, 20),(240, 430, 10, 20),(300, 430, 10, 20),(360, 430, 10, 20)]


class Ui_MainWindows(QtWidgets.QMainWindow):
    def __init__(self):
        super(Ui_MainWindows,self).__init__()
        self.central_widget = QtWidgets.QWidget()
        self.setCentralWidget(self.central_widget)
        self.setWindowTitle("Vision Room")

        self.buttons_KA = {}

        self.add_buttons_KA_IU()
        self.resize(1280, 960)


    def add_buttons_KA_IU(self):
        name_group = "button_KA"
        for i, geom in enumerate(positions_button_KA):
            b = QtWidgets.QPushButton(self.central_widget)
            b.setGeometry(*geom)
            path_image = os.path.join(dir_path, "Ressource/LightOff.png") 
            qss = 'border-image: url({})'.format(path_image)
            b.setStyleSheet(qss)

            self.buttons_KA[i] = b

def main():
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = Ui_MainWindows()
    MainWindow.show()

    rc = app.exec_()
    sys.exit(rc)


if __name__ == "__main__":
    main()