from Qt import QtCore, QtWidgets


class FindFileDialog(QtWidgets.QDialog):
    def __init__(self, editor, assistant):
        super().__init__(editor)
        self.currentAssistant = assistant
        self.currentEditor = editor

        self.createButtons()
        self.createComboBoxes()
        self.createFilesTree()
        self.createLabels()
        self.createLayout()

        self.directoryComboBox.addItem(
            QtCore.QDir.toNativeSeparators(QtCore.QDir.currentPath())
        )
        self.fileNameComboBox.addItem("*")
        self.findFiles()

        self.setWindowTitle(self.tr("Find File"))

    @QtCore.Slot()
    def browse(self):
        currentDirectory = self.directoryComboBox.currentText()
        newDirectory = QtWidgets.QFileDialog.getExistingDirectory(
            self, self.tr("Select Directory"), currentDirectory
        )
        if newDirectory:
            self.directoryComboBox.addItem(
                QtCore.QDir.toNativeSeparators(newDirectory)
            )
            self.directoryComboBox.setCurrentIndex(
                self.directoryComboBox.count() - 1
            )
            self.update()

    @QtCore.Slot()
    def help(self):
        self.currentAssistant.showDocumentation("filedialog.html")

    @QtCore.Slot("QTreeWidgetItem*")
    def openFile(self, item=None):
        if item is None:
            item = self.foundFilesTree.currentItem()
            if item is None:
                return
        fileName = item.text(0)
        path = self.directoryComboBox.currentText() + QtCore.QDir.separator()
        self.currentEditor.setContents(path + fileName)
        self.close()

    @QtCore.Slot()
    def update(self):
        self.findFiles()
        self.buttonBox.button(QtWidgets.QDialogButtonBox.Open).setEnabled(
            self.foundFilesTree.topLevelItemCount() > 0
        )

    def findFiles(self):
        filePattern = QtCore.QRegExp(self.fileNameComboBox.currentText() + "*")
        filePattern.setPatternSyntax(QtCore.QRegExp.Wildcard)

        directory = QtCore.QDir(self.directoryComboBox.currentText())

        allFiles = directory.entryList(
            QtCore.QDir.Files | QtCore.QDir.NoSymLinks
        )

        matchingFiles = []

        for file in allFiles:
            if filePattern.exactMatch(file):
                matchingFiles.append(file)

        self.showFiles(matchingFiles)

    def showFiles(self, files):
        self.foundFilesTree.clear()
        for file in files:
            item = QtWidgets.QTreeWidgetItem(self.foundFilesTree)
            item.setText(0, file)
        if files:
            self.foundFilesTree.setCurrentItem(
                self.foundFilesTree.topLevelItem(0)
            )

    def createButtons(self):
        self.browseButton = QtWidgets.QToolButton(
            text=self.tr("..."), clicked=self.browse
        )
        self.buttonBox = QtWidgets.QDialogButtonBox(
            QtWidgets.QDialogButtonBox.Open
            | QtWidgets.QDialogButtonBox.Cancel
            | QtWidgets.QDialogButtonBox.Help,
            accepted=self.openFile,
            rejected=self.reject,
            helpRequested=self.help,
        )

    def createComboBoxes(self):
        self.directoryComboBox = QtWidgets.QComboBox()
        self.fileNameComboBox = QtWidgets.QComboBox()
        self.fileNameComboBox.currentIndexChanged.connect(self.update)
        self.fileNameComboBox.editTextChanged.connect(self.update)

        self.fileNameComboBox.setEditable(True)
        self.fileNameComboBox.setSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred
        )

        self.directoryComboBox.setMinimumContentsLength(30)
        self.directoryComboBox.setSizeAdjustPolicy(
            QtWidgets.QComboBox.AdjustToMinimumContentsLength
        )
        self.directoryComboBox.setSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred
        )

    def createFilesTree(self):
        self.foundFilesTree = QtWidgets.QTreeWidget(
            columnCount=1,
            rootIsDecorated=False,
            selectionMode=QtWidgets.QAbstractItemView.SingleSelection,
        )
        self.foundFilesTree.itemActivated.connect(self.openFile)
        self.foundFilesTree.setHeaderLabels(self.tr("Matching Files"))

    def createLabels(self):
        self.directoryLabel = QtWidgets.QLabel(self.tr("Search in:"))
        self.fileNameLabel = QtWidgets.QLabel(
            self.tr("File name (including wildcards):")
        )

    def createLayout(self):
        fileLayout = QtWidgets.QHBoxLayout()
        fileLayout.addWidget(self.fileNameLabel)
        fileLayout.addWidget(self.fileNameComboBox)

        directoryLayout = QtWidgets.QHBoxLayout()
        directoryLayout.addWidget(self.directoryLabel)
        directoryLayout.addWidget(self.directoryComboBox)
        directoryLayout.addWidget(self.browseButton)

        mainLayout = QtWidgets.QVBoxLayout(self)
        mainLayout.addLayout(fileLayout)
        mainLayout.addLayout(directoryLayout)
        mainLayout.addWidget(self.foundFilesTree)
        mainLayout.addStretch()
        mainLayout.addWidget(self.buttonBox)
