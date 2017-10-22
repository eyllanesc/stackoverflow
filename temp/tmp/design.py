from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(640, 480)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.PS_timeSlider = QtWidgets.QSlider(self.centralwidget)
        self.PS_timeSlider.setGeometry(QtCore.QRect(100, 100, 371, 50))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding,
                                           QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.PS_timeSlider.sizePolicy().
                                     hasHeightForWidth())
        # needed to add a return and break the line above
        self.PS_timeSlider.setSizePolicy(sizePolicy)
        self.PS_timeSlider.setBaseSize(QtCore.QSize(0, 0))
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setKerning(False)
        self.PS_timeSlider.setFont(font)
        self.PS_timeSlider.setFocusPolicy(QtCore.Qt.WheelFocus)
        self.PS_timeSlider.setContextMenuPolicy(QtCore.Qt.NoContextMenu)
        self.PS_timeSlider.setToolTip("")
        self.PS_timeSlider.setStatusTip("")
        self.PS_timeSlider.setWhatsThis("")
        self.PS_timeSlider.setAccessibleName("")
        self.PS_timeSlider.setAccessibleDescription("")
        self.PS_timeSlider.setStyleSheet("QSlider::groove:horizontal {height: 10px; margin: 0 0;}\n"
                                         "QSlider::handle:horizontal {background: black;"
                                         "border: 1px; height: 40px; width: 40px; margin: 0 0;}\n")

        self.PS_timeSlider.setMinimum(0)
        self.PS_timeSlider.setMaximum(100)
        self.PS_timeSlider.setSingleStep(1)
        self.PS_timeSlider.setPageStep(5)
        self.PS_timeSlider.setProperty("value", 50)
        self.PS_timeSlider.setSliderPosition(50)
        self.PS_timeSlider.setTracking(True)
        self.PS_timeSlider.setOrientation(QtCore.Qt.Horizontal)
        self.PS_timeSlider.setInvertedAppearance(False)
        self.PS_timeSlider.setInvertedControls(False)
        self.PS_timeSlider.setTickPosition(QtWidgets.QSlider.TicksBothSides)
        self.PS_timeSlider.setTickInterval(1)
        self.PS_timeSlider.setObjectName("PS_timeSlider")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 640, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
