import os
import sys

from PySide2 import QtCore, QtWidgets, QtUiTools

# https://stackoverflow.com/a/42615559/6622587
if getattr(sys, 'frozen', False):
    # If the application is run as a bundle, the pyInstaller bootloader
    # extends the sys module by a flag frozen=True and sets the app 
    # path into variable _MEIPASS'.
    current_dir = os.path.join(sys._MEIPASS, "wizardUI")
else:
    current_dir = os.path.dirname(os.path.abspath(__file__))


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
            for file in os.listdir(current_dir):
                if file.startswith("{}.".format(cnt)):
                    ui_files.append(os.path.join(current_dir, file))
                    cnt += 1
        return ui_files

    def initPages(self, files):
        loader = QtUiTools.QUiLoader()
        for i in files:
            file = QtCore.QFile(str(i))
            if file.open(QtCore.QFile.ReadOnly):
                page = loader.load(file)
                self.addPage(page)
