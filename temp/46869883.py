import sys
from PyQt4.QtGui import *


class IndicSelectWindow(QDialog):
    def __init__(self, parent=None):
        super(IndicSelectWindow, self).__init__(parent=parent)
        # cero un layout vertical para las matrices
        layoutmatrices = QVBoxLayout()
        ##########################

        # create the area for the matrix
        scrollarea = QScrollArea()
        scrollarea.setWidgetResizable(True)
        widgetdelscrollarea = QWidget()
        self.layoutgrilla = QGridLayout(widgetdelscrollarea)
        scrollarea.setWidget(widgetdelscrollarea)
        ###########################

        # now now place elements in the array layout
        # the elements consist of a layout where the buttons are placed and another layout where the area is placed
        layoutelementosmatriz1 = QHBoxLayout()
        self.labelm1 = QLabel("Matriz 1")
        labelmf1 = QLabel("Filas")
        labelmc1 = QLabel("Columnas")
        botonm1 = QPushButton("Aceptar")
        text_m1f = QLineEdit()
        text_m1c = QLineEdit()
        layoutelementosmatriz1.addWidget(self.labelm1)
        layoutelementosmatriz1.addWidget(labelmf1)
        layoutelementosmatriz1.addWidget(text_m1f)
        layoutelementosmatriz1.addWidget(labelmc1)
        layoutelementosmatriz1.addWidget(text_m1c)
        layoutelementosmatriz1.addWidget(botonm1)
        layoutelementosmatriz1.setSpacing(20)

        botonm1.clicked.connect(lambda: self.create_matrix())  ##eventos

        layoutmatrices.addLayout(layoutelementosmatriz1)
        layoutmatrices.addWidget(scrollarea)

        ####################################3 i create the layout for the frame
        layoutgeneral = QHBoxLayout()
        self.setLayout(layoutgeneral)
        self.resize(800, 500)
        #################################
        # I add the elements to the frame
        layoutgeneral.addLayout(layoutmatrices)
        ###################################

    def create_matrix(self):  # this method I use to fill the array with "QLineEdit"
        self.labelm1.setText("gdsgs")
        for i in range(10):
            for j in range(10):
                self.layoutgrilla.addWidget(QLineEdit(), i, j)  # line 18


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = IndicSelectWindow()
    w.show()
    sys.exit(app.exec_())
