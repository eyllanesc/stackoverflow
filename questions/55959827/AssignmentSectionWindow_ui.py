# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uis/AssignmentSectionWindow.ui'
#
# Created by: PyQt5 UI code generator 5.12.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_AssignmentSectionWindow(object):
    def setupUi(self, AssignmentSectionWindow):
        AssignmentSectionWindow.setObjectName("AssignmentSectionWindow")
        AssignmentSectionWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(AssignmentSectionWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.assignmentLabel = QtWidgets.QLabel(self.centralwidget)
        self.assignmentLabel.setObjectName("assignmentLabel")
        self.gridLayout.addWidget(self.assignmentLabel, 0, 0, 1, 1)
        self.listWidget = QtWidgets.QListWidget(self.centralwidget)
        self.listWidget.setObjectName("listWidget")
        self.gridLayout.addWidget(self.listWidget, 1, 0, 1, 1)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.addAssignmentButton = QtWidgets.QPushButton(self.centralwidget)
        self.addAssignmentButton.setObjectName("addAssignmentButton")
        self.verticalLayout.addWidget(self.addAssignmentButton)
        self.editAssignmentButton = QtWidgets.QPushButton(self.centralwidget)
        self.editAssignmentButton.setObjectName("editAssignmentButton")
        self.verticalLayout.addWidget(self.editAssignmentButton)
        self.deleteAssignmentButton = QtWidgets.QPushButton(self.centralwidget)
        self.deleteAssignmentButton.setObjectName("deleteAssignmentButton")
        self.verticalLayout.addWidget(self.deleteAssignmentButton)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem)
        self.gridLayout.addLayout(self.verticalLayout, 1, 1, 1, 1)
        AssignmentSectionWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(AssignmentSectionWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 23))
        self.menubar.setObjectName("menubar")
        AssignmentSectionWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(AssignmentSectionWindow)
        self.statusbar.setObjectName("statusbar")
        AssignmentSectionWindow.setStatusBar(self.statusbar)

        self.retranslateUi(AssignmentSectionWindow)
        QtCore.QMetaObject.connectSlotsByName(AssignmentSectionWindow)

    def retranslateUi(self, AssignmentSectionWindow):
        _translate = QtCore.QCoreApplication.translate
        AssignmentSectionWindow.setWindowTitle(_translate("AssignmentSectionWindow", "Assignment Section"))
        self.assignmentLabel.setText(_translate("AssignmentSectionWindow", "Assignments of "))
        self.addAssignmentButton.setText(_translate("AssignmentSectionWindow", "Add Assignment"))
        self.editAssignmentButton.setText(_translate("AssignmentSectionWindow", "Edit Assignment"))
        self.deleteAssignmentButton.setText(_translate("AssignmentSectionWindow", "Delete Assignment"))


