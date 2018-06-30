import sys

from PyQt5 import QtCore, QtGui, QtWidgets, QtWebEngineWidgets, QtWebChannel


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(978, 704)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.formLayout = QtWidgets.QFormLayout(self.centralwidget)
        self.formLayout.setObjectName("formLayout")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.gumb_spoji = QtWidgets.QPushButton(self.centralwidget)
        self.gumb_spoji.setObjectName("gumb_spoji")
        
        self.verticalLayout.addWidget(self.gumb_spoji)
        self.link = QtWidgets.QLineEdit(self.centralwidget)
        self.link.setObjectName("link")
        self.verticalLayout.addWidget(self.link)
        self.pon = QtWidgets.QRadioButton(self.centralwidget)
        self.pon.setObjectName("pon")
        self.verticalLayout.addWidget(self.pon)
        self.uto = QtWidgets.QRadioButton(self.centralwidget)
        self.uto.setObjectName("uto")
        self.verticalLayout.addWidget(self.uto)
        self.sri = QtWidgets.QRadioButton(self.centralwidget)
        self.sri.setObjectName("sri")
        self.verticalLayout.addWidget(self.sri)
        self.cet = QtWidgets.QRadioButton(self.centralwidget)
        self.cet.setObjectName("cet")
        self.verticalLayout.addWidget(self.cet)
        self.pet = QtWidgets.QRadioButton(self.centralwidget)
        self.pet.setObjectName("pet")
        self.verticalLayout.addWidget(self.pet)
        self.sub = QtWidgets.QRadioButton(self.centralwidget)
        self.sub.setObjectName("sub")
        self.verticalLayout.addWidget(self.sub)
        self.ned = QtWidgets.QRadioButton(self.centralwidget)
        self.ned.setObjectName("ned")
        self.verticalLayout.addWidget(self.ned)
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.verticalLayout.addWidget(self.comboBox)
        self.gumb_dohvati = QtWidgets.QPushButton(self.centralwidget)
        self.gumb_dohvati.setObjectName("gumb_dohvati")
        

        self.verticalLayout.addWidget(self.gumb_dohvati)
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)
        self.mean = QtWidgets.QLineEdit(self.centralwidget)
        self.mean.setObjectName("mean")
        self.verticalLayout.addWidget(self.mean)
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setObjectName("label_2")
        self.verticalLayout.addWidget(self.label_2)
        self.median = QtWidgets.QLineEdit(self.centralwidget)
        self.median.setObjectName("median")
        self.verticalLayout.addWidget(self.median)
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setObjectName("label_3")
        self.verticalLayout.addWidget(self.label_3)
        self.std = QtWidgets.QLineEdit(self.centralwidget)
        self.std.setObjectName("std")
        self.verticalLayout.addWidget(self.std)
        self.formLayout.setLayout(0, QtWidgets.QFormLayout.LabelRole, 
        self.verticalLayout)

        
        self.mapa = QtWidgets.QWidget(self.centralwidget)
        self.mapa.setObjectName("mapa")
        self.mapa = QtWebEngineWidgets.QWebEngineView(self.centralwidget)
       
        self.formLayout_3 = QtWidgets.QFormLayout(self.mapa)
        self.formLayout_3.setObjectName("formLayout_3")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.mapa)
        self.graf = QtWidgets.QWidget(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(255)

        sizePolicy.setHeightForWidth(self.graf.sizePolicy().hasHeightForWidth())
        self.graf.setSizePolicy(sizePolicy)
        self.graf.setMouseTracking(True)
        self.graf.setObjectName("graf")
        self.graf = QtWebEngineWidgets.QWebEngineView(self.centralwidget)
        self.formLayout_2 = QtWidgets.QFormLayout(self.graf)
        self.formLayout_2.setObjectName("formLayout_2")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.SpanningRole, 
        self.graf)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 978, 21))
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
        self.gumb_spoji.setText(_translate("MainWindow", "Spoji se na bazu"))
        self.pon.setText(_translate("MainWindow", "Ponedjeljak"))
        self.uto.setText(_translate("MainWindow", "Utorak"))
        self.sri.setText(_translate("MainWindow", "Srijeda"))
        self.cet.setText(_translate("MainWindow", "Cetvrtak"))
        self.pet.setText(_translate("MainWindow", "Petak"))
        self.sub.setText(_translate("MainWindow", "Subota"))
        self.ned.setText(_translate("MainWindow", "Nedjelja"))
        self.comboBox.setItemText(0, _translate("MainWindow", "5min"))
        self.comboBox.setItemText(1, _translate("MainWindow", "15min"))
        self.gumb_dohvati.setText(_translate("MainWindow", "Dohvati podatke"))
        self.label.setText(_translate("MainWindow", "Srednja vrijednost"))
        self.label_2.setText(_translate("MainWindow", "Median"))
        self.label_3.setText(_translate("MainWindow", "Standardna devijacija"))


class AppMainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(AppMainWindow, self).__init__(parent)
        self.setupUi(self)
        #backend.pointChanged.connect(self.onPointChanged)
        channel = QtWebChannel.QWebChannel(self)
        channel.registerObject('mainwindow', self)
        self.mapa.page().setWebChannel(channel)

        file = QtCore.QDir.current().absoluteFilePath("index.html")
        self.mapa.load(QtCore.QUrl.fromLocalFile(file))

    @QtCore.pyqtSlot(float,float)
    def pointClicked(self, x, y):
        print("new points")
        print(x, y)

if __name__ == "__main__":
    import sys
    app = QtCore.QCoreApplication.instance()
    if app is None:
        app = QtWidgets.QApplication(sys.argv)
    w = AppMainWindow()
    w.show()
    sys.exit(app.exec_())