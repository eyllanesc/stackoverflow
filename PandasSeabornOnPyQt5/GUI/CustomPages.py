from PyQt5.QtCore import QDir, pyqtSignal
from PyQt5.QtWidgets import QVBoxLayout, QHBoxLayout, QTextBrowser, QPushButton, QSpacerItem, QSizePolicy, QFileDialog, \
    QScrollArea, QAbstractScrollArea, QWidget, QLabel, QComboBox, QCheckBox, QButtonGroup

from config import content1, content2, content3
from libPage import Page


class FirstPage(Page):
    changeFilename = pyqtSignal(str)

    def __init__(self, parent=None):
        Page.__init__(self, parent=parent)
        self.setLayout(QVBoxLayout())

        tb = QTextBrowser(self)
        tb.setHtml(content1)

        self.layout().addWidget(tb)

        hbox = QHBoxLayout()

        btn = QPushButton(self)
        btn.setText("File picker to load the  CSV file from user's disk.")

        btn.clicked.connect(self.loadFilename)
        hbox.addWidget(btn)

        item = QSpacerItem(1, 1, QSizePolicy.Expanding, QSizePolicy.Fixed)
        hbox.addItem(item)

        self.layout().addLayout(hbox)

    def loadFilename(self):
        fileName, _ = QFileDialog.getOpenFileName(self,
                                                  "Open CSV File",
                                                  QDir.currentPath(),
                                                  "CSV Files (*.csv)")

        if fileName != "":
            self.changeFilename.emit(fileName)
            self.finished.emit()


class SecongPage(Page):
    changeCkeckbox = pyqtSignal()

    def __init__(self, parent=None):
        QWidget.__init__(self, parent=parent)
        self.setLayout(QHBoxLayout())

        vbox = QVBoxLayout()

        self.layout().addLayout(vbox)

        scrollArea = QScrollArea(self)

        scrollArea.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        scrollArea.setWidgetResizable(True)

        contentWidget = QWidget()
        contentWidget.setStyleSheet(".QWidget{background-color: rgb(255, 255, 255);}")
        scrollArea.setWidget(contentWidget)
        contentWidget.setLayout(QVBoxLayout())

        vbox.addWidget(QLabel("<b>One Column Name:</b>", contentWidget))
        self.oneComboBox = QComboBox(contentWidget)
        vbox.addWidget(self.oneComboBox)
        vbox.addWidget(QLabel("<b>Column names:</b>", contentWidget))

        self.checkBoxLayout = QVBoxLayout()
        contentWidget.layout().addLayout(self.checkBoxLayout)

        spacerItem = QSpacerItem(1, 1, QSizePolicy.Minimum, QSizePolicy.Expanding)
        contentWidget.layout().addItem(spacerItem)

        processBtn = QPushButton("Process")
        processBtn.clicked.connect(self.finished.emit)

        vbox.addWidget(scrollArea)
        vbox.addWidget(processBtn)

        textBrowser = QTextBrowser(self)
        textBrowser.setHtml(content2)

        self.layout().addWidget(textBrowser)

        self.layout().setStretch(0, 1)
        self.layout().setStretch(1, 1)
        self.checkboxs = []
        self.oneComboBox.currentIndexChanged.connect(self.configElements)

    def setFields(self, fields):
        print("set Fields")
        self.oneComboBox.blockSignals(True)
        self.oneComboBox.clear()
        self.oneComboBox.addItems(fields)
        self.oneComboBox.blockSignals(False)

        for w in self.checkboxs:
            w.deleteLater()
        self.checkboxs = []

        for text in fields:
            ch = QCheckBox(text)
            ch.setChecked(True)
            ch.stateChanged.connect(self.changeCkeckbox.emit)
            self.checkBoxLayout.addWidget(ch)
            self.checkboxs.append(ch)

        self.configElements()

    def configElements(self):
        current_text = self.oneComboBox.currentText()

        for checkbox in self.checkboxs:
            if checkbox.text() == current_text:
                checkbox.hide()
                checkbox.blockSignals(True)
                checkbox.setChecked(True)
                checkbox.blockSignals(False)
            else:
                checkbox.show()


class ThirdPage(Page):
    def __init__(self, parent=None):
        Page.__init__(self, parent=parent)
        self.setLayout(QVBoxLayout())
        textBrowser = QTextBrowser()
        self.layout().addWidget(textBrowser)
        textBrowser.setHtml(content3)
