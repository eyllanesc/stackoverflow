import sys
from functools import partial
from shutil import copyfile

# import vispy.mpl_plot as plt
import vispy.app

vispy.app.use_app(backend_name="PyQt5", call_reuse=True)

# here we import canvasCreater call from run.py file
from run import canvasCreater

# from PyQt5.QtWidgets import (QApplication,QFrame, QCheckBox,QGridLayout, QHBoxLayout, QPushButton, QSizePolicy, QSpacerItem, QToolButton, QVBoxLayout, QWidget,
# QGridLayout,QFileDialog,QRadioButton,QMainWindow)
from PyQt5.QtWidgets import *


class Widget(QWidget, canvasCreater):
    filenames_list = []

    def __init__(self, parent=None):
        super(Widget, self).__init__(parent=parent)
        self.measurements = self.load_config()
        self.m_f = "models"
        self.r_f = "results"
        self.layoutUI()

    def layoutUI(self):
        self.setStyleSheet("background-color: white;")

        self.principalLayout = QHBoxLayout(self)

        self.leftFrame = QFrame(self)
        self.leftFrame.setFrameShape(QFrame.StyledPanel)
        self.leftFrame.setFrameShadow(QFrame.Raised)
        self.verticalLayout = QVBoxLayout(self.leftFrame)

        self.principalLayout.addWidget(self.leftFrame)

        self.verticalLayoutR = QVBoxLayout()
        # self.verticalLayoutR.setSpacing(0)

        self.keyFrame = QFrame(self)
        # self.keyFrame.setStyleSheet("background-color: red;")
        self.keyFrame.setFrameShape(QFrame.StyledPanel)
        self.keyFrame.setFrameShadow(QFrame.Raised)

        self.keysverticalLayout = QVBoxLayout(self.keyFrame)

        self.AddBtn = QPushButton("Add", self.keyFrame)
        self.SelectBtn = QPushButton("Select", self.keyFrame)
        self.RunBtn = QPushButton("Run", self.keyFrame)
        self.StopBtn = QPushButton("Stop", self.keyFrame)

        ##################################################
        self.keysverticalLayout.addWidget(self.AddBtn)
        self.AddBtn.clicked.connect(self.AddItem)

        ##################################################
        self.keysverticalLayout.addWidget(self.SelectBtn)
        self.SelectBtn.clicked.connect(self.SelectItem)

        #################################################
        self.viewFrame = QFrame(self)
        self.viewFrame.setFrameShape(QFrame.StyledPanel)
        self.viewFrame.setFrameShadow(QFrame.Raised)
        self.gridLayout = QGridLayout(self.viewFrame)

        # self.verticalLayout.addStretch(1)
        self.cb = QCheckBox(self.viewFrame)
        self.cb.stateChanged.connect(self.checkBox)
        ###################################################
        self.ViewBtn = QPushButton("View", self.viewFrame)
        self.ViewBtn.clicked.connect(self.ViewItem)

        self.gridLayout.addWidget(self.cb, 0, 0)
        self.gridLayout.addWidget(self.ViewBtn, 0, 1)

        # self.ViewBtn.move(0,50)


        self.keysverticalLayout.addWidget(self.viewFrame)

        # self.keysverticalLayout.addWidget(self.ViewBtn)
        #####################################################
        self.keysverticalLayout.addWidget(self.RunBtn)
        self.RunBtn.clicked.connect(self.RunItem)

        ###################################################
        self.keysverticalLayout.addWidget(self.StopBtn)
        self.StopBtn.clicked.connect(self.StopItem)

        self.verticalLayoutR.addWidget(self.keyFrame)
        self.principalLayout.addLayout(self.verticalLayoutR)

        self.rightFrame = QFrame(self)
        self.rightFrame.setFrameShape(QFrame.StyledPanel)
        self.rightFrame.setFrameShadow(QFrame.Raised)
        self.verticalLayoutRight = QVBoxLayout(self.rightFrame)

        self.principalLayout.addWidget(self.rightFrame)

    def AddItem(self):
        file_name_list = []
        fname = QFileDialog.getOpenFileName(self, 'Open file', '/')

        file_selected = str(fname[0])
        # print(file_selected)
        file_name_list = file_selected.split('/')

        final_file_name = file_name_list[-1]
        Widget.filenames_list.append(final_file_name)

        path = str(fname[0])

        dst = "/home/raw-at/Desktop/pyqt5/models/" + final_file_name

        # print(final_file_name)

        copyfile(path, dst)

    def SelectItem(self):
        for i in range(len(Widget.filenames_list)):
            print(i)
            name = "obj" + str(i)

            self.name = QRadioButton(self.filenames_list[i], self.rightFrame)
            self.verticalLayoutRight.addWidget(self.name)

    def ViewItem(self):
        # sp.Popen("python3 run.py debug 1.obj",shell=True)
        # self.debug()

        # here we call the debug function of the imported class
        canvas = self.debug(self.measurements, "models/1.obj", False)
        canvas.create_native()
        canvas.native.setMinimumSize(320, 240)
        self.verticalLayoutRight.addWidget(canvas.native)

        # here i just want to embed the output genereated by the self.debug to
        # Put into the right QFrame of the Gui
        # see debug funtion in run.py for other references


    def RunItem(self):
        pass

    def StopItem(self):
        print('Stop button')

    def checkBox(self):
        print("Check Box")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Widget()

    # measurements = w.load_config()

    # folder names
    # m_f = "models"
    # r_f = "results"

    w.show()
    sys.exit(app.exec_())

    # getting info from config file
    # canvasObj = canvasCreater()
    # measurements = w.load_config()

    # folder names
    # m_f = "models"
    # r_f = "results"

    # debug or all file calculations
    '''
    if len(sys.argv) == 3 and sys.argv[1] == "debug":
        w.debug(measurements, "{0}/{1}".format(m_f,sys.argv[2]), False)
    elif len(sys.argv) == 3 and sys.argv[1] == "debug_full":
        w.debug(measurements, "{0}/{1}".format(m_f,sys.argv[2]), True)
    elif len(sys.argv) == 1:
        w.calculate_all(measurements, m_f, r_f)
    else:
        print("Wrong input format, refer to instruction manual.")
    '''
