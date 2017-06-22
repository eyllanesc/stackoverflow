# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.8.2
#
# WARNING! All changes made in this file will be lost!

import os
import sys
#import Logo_rc
from PyQt5.QtCore import pyqtSignal, QObject
import subprocess
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QWidget, QDialog,QAction
import ValveSim

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(956, 735)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("//Zvi-ad-001/zvi/Engineering/Workspace/David/Excel Projects/Untitled.bmp"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.mdiArea = QtWidgets.QMdiArea(self.centralwidget)
        self.mdiArea.setActivationOrder(QtWidgets.QMdiArea.StackingOrder)
        self.mdiArea.setObjectName("mdiArea")
        self.gridLayout.addWidget(self.mdiArea, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 956, 21))
        self.menubar.setObjectName("menubar")
        self.menuFile = QtWidgets.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuSettings = QtWidgets.QMenu(self.menuFile)
        self.menuSettings.setObjectName("menuSettings")
        self.menuRun = QtWidgets.QMenu(self.menubar)
        self.menuRun.setObjectName("menuRun")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionMSA = QtWidgets.QAction(MainWindow)
        self.actionMSA.setObjectName("actionMSA")
        self.actionComparison = QtWidgets.QAction(MainWindow)
        self.actionComparison.setObjectName("actionComparison")
        self.actionMetal_Sizing = QtWidgets.QAction(MainWindow)
        self.actionMetal_Sizing.setObjectName("actionMetal_Sizing")
        self.actionMass_Fraction_Calculator = QtWidgets.QAction(MainWindow)
        self.actionMass_Fraction_Calculator.setObjectName("actionMass_Fraction_Calculator")
        self.actionModule_Program = QtWidgets.QAction(MainWindow)
        self.actionModule_Program.setObjectName("actionModule_Program")
        self.actionExit = QtWidgets.QAction(MainWindow)
        self.actionExit.setObjectName("actionExit")
        self.actionWorking_Directory = QtWidgets.QAction(MainWindow)
        self.actionWorking_Directory.setObjectName("actionWorking_Directory")
        self.actionValve_Simulator = QtWidgets.QAction(MainWindow)
        self.actionValve_Simulator.setObjectName("actionValve_Simulator")
        self.menuSettings.addAction(self.actionWorking_Directory)
        self.menuFile.addAction(self.menuSettings.menuAction())
        self.menuFile.addAction(self.actionExit)
        self.menuRun.addAction(self.actionMSA)
        self.menuRun.addAction(self.actionComparison)
        self.menuRun.addAction(self.actionMetal_Sizing)
        self.menuRun.addAction(self.actionMass_Fraction_Calculator)
        self.menuRun.addAction(self.actionModule_Program)
        self.menuRun.addAction(self.actionValve_Simulator)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuRun.menuAction())


        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "ZVI"))
        self.menuFile.setTitle(_translate("MainWindow", "File"))
        self.menuSettings.setTitle(_translate("MainWindow", "Settings"))
        self.menuRun.setTitle(_translate("MainWindow", "Run"))
        self.actionMSA.setText(_translate("MainWindow", "MSA"))
        self.actionComparison.setText(_translate("MainWindow", "Comparison"))
        self.actionMetal_Sizing.setText(_translate("MainWindow", "Metal Sizing"))
        self.actionMass_Fraction_Calculator.setText(_translate("MainWindow", "Mass Fraction Calculator"))
        self.actionModule_Program.setText(_translate("MainWindow", "Module Program"))
        self.actionExit.setText(_translate("MainWindow", "Exit"))
        self.actionWorking_Directory.setText(_translate("MainWindow", "Working Directory"))
        self.actionValve_Simulator.setText(_translate("MainWindow", "Valve Simulator"))
