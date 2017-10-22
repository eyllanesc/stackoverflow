# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'dynotest1.ui'
#
# Created by: PyQt5 UI code generator 5.9
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_DynoTest1(object):
    def setupUi(self, DynoTest1):
        DynoTest1.setObjectName("DynoTest1")
        DynoTest1.resize(1001, 695)
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(DynoTest1)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.pushButton_2 = QtWidgets.QPushButton(DynoTest1)
        self.pushButton_2.setObjectName("pushButton_2")
        self.gridLayout.addWidget(self.pushButton_2, 1, 0, 1, 1)
        self.pushButton_4 = QtWidgets.QPushButton(DynoTest1)
        self.pushButton_4.setObjectName("pushButton_4")
        self.gridLayout.addWidget(self.pushButton_4, 1, 1, 1, 1)
        self.pushButton_3 = QtWidgets.QPushButton(DynoTest1)
        self.pushButton_3.setObjectName("pushButton_3")
        self.gridLayout.addWidget(self.pushButton_3, 0, 1, 1, 1)
        self.pushButton = QtWidgets.QPushButton(DynoTest1)
        self.pushButton.setObjectName("pushButton")
        self.gridLayout.addWidget(self.pushButton, 0, 0, 1, 1)
        self.verticalLayout_3.addLayout(self.gridLayout)
        self.label_3 = QtWidgets.QLabel(DynoTest1)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_3.addWidget(self.label_3)
        self.label_2 = QtWidgets.QLabel(DynoTest1)
        self.label_2.setObjectName("label_2")
        self.verticalLayout_3.addWidget(self.label_2)
        self.label = QtWidgets.QLabel(DynoTest1)
        self.label.setObjectName("label")
        self.verticalLayout_3.addWidget(self.label)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.label_5 = QtWidgets.QLabel(DynoTest1)
        self.label_5.setObjectName("label_5")
        self.verticalLayout.addWidget(self.label_5)
        self.lcdNumber_4 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_4.setObjectName("lcdNumber_4")
        self.verticalLayout.addWidget(self.lcdNumber_4)
        self.lcdNumber_5 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_5.setObjectName("lcdNumber_5")
        self.verticalLayout.addWidget(self.lcdNumber_5)
        self.lcdNumber_6 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_6.setObjectName("lcdNumber_6")
        self.verticalLayout.addWidget(self.lcdNumber_6)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_6 = QtWidgets.QLabel(DynoTest1)
        self.label_6.setObjectName("label_6")
        self.verticalLayout_2.addWidget(self.label_6)
        self.lcdNumber = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber.setObjectName("lcdNumber")
        self.verticalLayout_2.addWidget(self.lcdNumber)
        self.lcdNumber_2 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_2.setObjectName("lcdNumber_2")
        self.verticalLayout_2.addWidget(self.lcdNumber_2)
        self.lcdNumber_3 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_3.setObjectName("lcdNumber_3")
        self.verticalLayout_2.addWidget(self.lcdNumber_3)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.horizontalLayout_2.addLayout(self.horizontalLayout)
        self.verticalLayout_5 = QtWidgets.QVBoxLayout()
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.label_7 = QtWidgets.QLabel(DynoTest1)
        self.label_7.setObjectName("label_7")
        self.verticalLayout_5.addWidget(self.label_7)
        self.lcdNumber_7 = QtWidgets.QLCDNumber(DynoTest1)
        self.lcdNumber_7.setObjectName("lcdNumber_7")
        self.verticalLayout_5.addWidget(self.lcdNumber_7)
        self.horizontalLayout_2.addLayout(self.verticalLayout_5)
        self.verticalLayout_4.addLayout(self.horizontalLayout_2)
        self.graphicsView = QtWidgets.QGraphicsView(DynoTest1)
        self.graphicsView.setStyleSheet("border-image: url(:/newPrefix/husky_head5.png);")
        self.graphicsView.setObjectName("graphicsView")
        self.verticalLayout_4.addWidget(self.graphicsView)

        self.retranslateUi(DynoTest1)
        QtCore.QMetaObject.connectSlotsByName(DynoTest1)

    def retranslateUi(self, DynoTest1):
        _translate = QtCore.QCoreApplication.translate
        DynoTest1.setWindowTitle(_translate("DynoTest1", "DynoTest1"))
        self.pushButton_2.setText(_translate("DynoTest1", "Pause"))
        self.pushButton_4.setText(_translate("DynoTest1", "Print"))
        self.pushButton_3.setText(_translate("DynoTest1", "Stop"))
        self.pushButton.setText(_translate("DynoTest1", "Start"))
        self.label_3.setText(_translate("DynoTest1",
                                        "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">RPMs</span></p></body></html>"))
        self.label_2.setText(_translate("DynoTest1",
                                        "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Torque (ft-lbs)</span></p></body></html>"))
        self.label.setText(_translate("DynoTest1",
                                      "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Horse Power</span></p></body></html>"))
        self.label_5.setText(_translate("DynoTest1",
                                        "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Now</span></p></body></html>"))
        self.label_6.setText(_translate("DynoTest1",
                                        "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Max</span></p></body></html>"))
        self.label_7.setText(_translate("DynoTest1",
                                        "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Run Time</span></p></body></html>"))

        #  import Resource_rc
