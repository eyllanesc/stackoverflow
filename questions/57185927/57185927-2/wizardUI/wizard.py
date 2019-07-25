from PySide2 import QtCore, QtWidgets, QtUiTools


class tutorWizard(QtWidgets.QWizard):
    """ Contains introduction tutorial """

    def __init__(self, parent=None):
        super(tutorWizard, self).__init__(parent)

        self.setWindowTitle("Introduction tutorial")
        pages = self.findPages()
        self.initPages(pages)

    def findPages(self):
        ui_files = []
        cnt = 1

        while len(ui_files) < 15:
            it = QtCore.QDirIterator(":/wizardUI")
            while it.hasNext():
                filename = it.next()
                name = QtCore.QFileInfo(filename).fileName()
                if name.startswith("{}.".format(cnt)):
                    ui_files.append(filename)
                    cnt += 1

        return ui_files

    def initPages(self, files):
        loader = QtUiTools.QUiLoader()
        for i in files:
            file = QtCore.QFile(str(i))
            if file.open(QtCore.QFile.ReadOnly):
                page = loader.load(file)
                self.addPage(page)
