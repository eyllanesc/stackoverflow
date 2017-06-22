# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ValveSim.ui'
#
# Created by: PyQt5 UI code generator 5.8.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_ValveSim(object):
    def setupUi(self, ValveSim):
        ValveSim.setObjectName("ValveSim")
        ValveSim.resize(685, 833)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("E:/Workspace/Projects2/Python/Icon.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        ValveSim.setWindowIcon(icon)
        ValveSim.setWindowOpacity(1.0)
        ValveSim.setAutoFillBackground(True)
        self.MainWidget = QtWidgets.QWidget(ValveSim)
        self.MainWidget.setObjectName("MainWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.MainWidget)
        self.gridLayout.setObjectName("gridLayout")
        ValveSim.setCentralWidget(self.MainWidget)
        self.menubar = QtWidgets.QMenuBar(ValveSim)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 685, 21))
        self.menubar.setObjectName("menubar")
        self.menuFile = QtWidgets.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuEdit = QtWidgets.QMenu(self.menubar)
        self.menuEdit.setObjectName("menuEdit")
        self.menuRun = QtWidgets.QMenu(self.menubar)
        self.menuRun.setObjectName("menuRun")
        self.menuHelp = QtWidgets.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        ValveSim.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(ValveSim)
        self.statusbar.setObjectName("statusbar")
        ValveSim.setStatusBar(self.statusbar)
        self.actionRead_Input = QtWidgets.QAction(ValveSim)
        self.actionRead_Input.setObjectName("actionRead_Input")
        self.actionSave_Input = QtWidgets.QAction(ValveSim)
        self.actionSave_Input.setObjectName("actionSave_Input")
        self.actionSettings = QtWidgets.QAction(ValveSim)
        self.actionSettings.setObjectName("actionSettings")
        self.actionMetal_Sizing = QtWidgets.QAction(ValveSim)
        self.actionMetal_Sizing.setObjectName("actionMetal_Sizing")
        self.actionModule_Program = QtWidgets.QAction(ValveSim)
        self.actionModule_Program.setObjectName("actionModule_Program")
        self.actionMSA = QtWidgets.QAction(ValveSim)
        self.actionMSA.setObjectName("actionMSA")
        self.menuFile.addAction(self.actionRead_Input)
        self.menuFile.addAction(self.actionSave_Input)
        self.menuFile.addAction(self.actionSettings)
        self.menuRun.addAction(self.actionMetal_Sizing)
        self.menuRun.addAction(self.actionModule_Program)
        self.menuRun.addAction(self.actionMSA)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuEdit.menuAction())
        self.menubar.addAction(self.menuRun.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(ValveSim)
        QtCore.QMetaObject.connectSlotsByName(ValveSim)

    def retranslateUi(self, ValveSim):
        _translate = QtCore.QCoreApplication.translate
        ValveSim.setWindowTitle(_translate("ValveSim", "ZVI Simulator"))
        self.menuFile.setTitle(_translate("ValveSim", "File"))
        self.menuEdit.setTitle(_translate("ValveSim", "Edit"))
        self.menuRun.setTitle(_translate("ValveSim", "Run"))
        self.menuHelp.setTitle(_translate("ValveSim", "Help"))
        self.actionRead_Input.setText(_translate("ValveSim", "Read Input"))
        self.actionSave_Input.setText(_translate("ValveSim", "Save Input"))
        self.actionSettings.setText(_translate("ValveSim", "Settings"))
        self.actionMetal_Sizing.setText(_translate("ValveSim", "Metal Sizing"))
        self.actionModule_Program.setText(_translate("ValveSim", "Module Program"))
        self.actionMSA.setText(_translate("ValveSim", "MSA"))

#import Logo_rc


