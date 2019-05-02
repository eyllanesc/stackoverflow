# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uis/AddAssignmentDialog.ui'
#
# Created by: PyQt5 UI code generator 5.12.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_AddAssignmentDialog(object):
    def setupUi(self, AddAssignmentDialog):
        AddAssignmentDialog.setObjectName("AddAssignmentDialog")
        AddAssignmentDialog.resize(400, 300)
        self.formLayout_4 = QtWidgets.QFormLayout(AddAssignmentDialog)
        self.formLayout_4.setObjectName("formLayout_4")
        self.assignmentNameLabel = QtWidgets.QLabel(AddAssignmentDialog)
        self.assignmentNameLabel.setObjectName("assignmentNameLabel")
        self.formLayout_4.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.assignmentNameLabel)
        self.assignmentNameLine = QtWidgets.QLineEdit(AddAssignmentDialog)
        self.assignmentNameLine.setObjectName("assignmentNameLine")
        self.formLayout_4.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.assignmentNameLine)
        self.dueLabel = QtWidgets.QLabel(AddAssignmentDialog)
        self.dueLabel.setObjectName("dueLabel")
        self.formLayout_4.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.dueLabel)
        self.dueLine = QtWidgets.QLineEdit(AddAssignmentDialog)
        self.dueLine.setObjectName("dueLine")
        self.formLayout_4.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.dueLine)
        self.uploadFileLabel = QtWidgets.QLabel(AddAssignmentDialog)
        self.uploadFileLabel.setObjectName("uploadFileLabel")
        self.formLayout_4.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.uploadFileLabel)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.uploadFileNameLine = QtWidgets.QLineEdit(AddAssignmentDialog)
        self.uploadFileNameLine.setObjectName("uploadFileNameLine")
        self.horizontalLayout.addWidget(self.uploadFileNameLine)
        self.browseButton = QtWidgets.QPushButton(AddAssignmentDialog)
        self.browseButton.setObjectName("browseButton")
        self.horizontalLayout.addWidget(self.browseButton)
        self.formLayout_4.setLayout(2, QtWidgets.QFormLayout.FieldRole, self.horizontalLayout)
        self.descriptionLabel = QtWidgets.QLabel(AddAssignmentDialog)
        self.descriptionLabel.setObjectName("descriptionLabel")
        self.formLayout_4.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.descriptionLabel)
        self.descriptionText = QtWidgets.QTextEdit(AddAssignmentDialog)
        self.descriptionText.setObjectName("descriptionText")
        self.formLayout_4.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.descriptionText)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.submitButton = QtWidgets.QPushButton(AddAssignmentDialog)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Maximum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.submitButton.sizePolicy().hasHeightForWidth())
        self.submitButton.setSizePolicy(sizePolicy)
        self.submitButton.setObjectName("submitButton")
        self.horizontalLayout_2.addWidget(self.submitButton)
        self.formLayout_4.setLayout(4, QtWidgets.QFormLayout.FieldRole, self.horizontalLayout_2)

        self.retranslateUi(AddAssignmentDialog)
        QtCore.QMetaObject.connectSlotsByName(AddAssignmentDialog)

    def retranslateUi(self, AddAssignmentDialog):
        _translate = QtCore.QCoreApplication.translate
        AddAssignmentDialog.setWindowTitle(_translate("AddAssignmentDialog", "Dialog"))
        self.assignmentNameLabel.setText(_translate("AddAssignmentDialog", "Assignment Name"))
        self.dueLabel.setText(_translate("AddAssignmentDialog", "Assignment Due"))
        self.uploadFileLabel.setText(_translate("AddAssignmentDialog", "Upload File"))
        self.browseButton.setText(_translate("AddAssignmentDialog", "Browse"))
        self.descriptionLabel.setText(_translate("AddAssignmentDialog", "Description"))
        self.submitButton.setText(_translate("AddAssignmentDialog", "Submit"))


