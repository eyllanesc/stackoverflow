from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_tmy3page(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(900, 620)
        MainWindow.setMinimumSize(QtCore.QSize(900, 620))
        MainWindow.setMaximumSize(QtCore.QSize(900, 620))
        MainWindow.setWindowTitle("")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.html_code = QtWebEngineWidgets.QWebEngineView(self.centralwidget)
        self.html_code.setGeometry(QtCore.QRect(0, 0, 901, 621))
        self.html_code.setUrl(QtCore.QUrl("about:blank"))
        self.html_code.setObjectName("html_code")
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        pass


from PyQt5 import QtWebEngineWidgets
