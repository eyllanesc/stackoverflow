# -*- coding: utf-8 -*-
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.uic import loadUiType
import youtube_dl
import pafy
import urllib.request
import urllib.parse
from urllib.parse import *
import win32clipboard
import sys
import os
import humanize
import subprocess
import time
import shutil
import re
from pySmartDL import SmartDL
from os.path import splitext, basename
from os import path

if getattr(sys, 'frozen', False):
    # frozen
    dir_ = os.path.dirname(sys.executable)
else:
    # unfrozen
    dir_ = os.path.dirname(os.path.realpath(__file__))
FORM_CLASS, _ = loadUiType(path.join(dir_, "main.ui"))


class DownloadThread(QThread):
    dataChanged = pyqtSignal(int, str, str, str)
    Started, Paused, Resume, Stopped = range(4)
    downloadError = pyqtSignal()
    downloadFinished = pyqtSignal()

    def __init__(self, parent=None):
        QThread.__init__(self, parent)
        self.state = DownloadThread.Stopped
        self.params = {"url": "", "save_location": ""}

    def setParams(self, params):
        self.params = params

    def setState(self, state):
        self.state = state

    def run(self):
        obj = SmartDL(self.params["url"], progress_bar=False)
        try:
            obj.start(blocking=False)
            while True:
                self.dataChanged.emit(obj.get_progress() * 100,
                                      str(obj.get_dl_size(human=True)),
                                      str(obj.get_speed(human=True)),
                                      str(obj.get_eta(human=True)))
                time.sleep(0.2)
                if self.state == DownloadThread.Paused:
                    obj.pause()
                if self.state == DownloadThread.Resume:
                    obj.unpause()
                    self.state = DownloadThread.Started
                if obj.isFinished():
                    break
                if self.state == DownloadThread.Stopped:
                    obj.stop()
                    self.progressBar.setValue(0)
                    break
            if obj.isSuccessful():
                # os.rename(obj.get_dest(), save_location)
                shutil.move(obj.get_dest(), self.params["save_location"])
                if self.state == DownloadThread.Started:
                    self.downloadFinished.emit()
        except:
            self.downloadError.emit()


class MainApp(QMainWindow, FORM_CLASS):
    def __init__(self, parent=None):
        super(MainApp, self).__init__(parent)
        QMainWindow.__init__(self)
        self.setupUi(self)
        self.lineEdit.installEventFilter(self)
        self.lineEdit_3.installEventFilter(self)
        self.lineEdit_6.installEventFilter(self)
        self.Handle_Ui()
        self.Handle_Buttons()
        self.download = DownloadThread(self)
        self.download.dataChanged.connect(self.onDataChanged)
        self.download.downloadError.connect(self.errorDownload)
        self.download.downloadFinished.connect(self.successfulDownload)

    def closeEvent(self, evnt):
        if self._want_to_close:
            super(MainApp, self).closeEvent(evnt)
            sys.exit()

    def Handle_Ui(self):
        # self.lineEdit.setFocus()
        self.setFixedSize(861, 441)

    def Handle_Buttons(self):
        self.pushButton_3.clicked.connect(self.open_file_loction)
        self.pushButton_2.clicked.connect(self.Start)
        self.pushButton_13.clicked.connect(self.Pause)
        self.pushButton_14.clicked.connect(self.Stop)
        self.pushButton.clicked.connect(self.Handle_Browse)
        self.pushButton_4.clicked.connect(self.Download_youtube_video)
        self.pushButton_10.clicked.connect(self.get_quality)
        self.pushButton_5.clicked.connect(self.Browse2)
        self.pushButton_6.clicked.connect(self.open_file_location2)
        self.pushButton_11.clicked.connect(self.Search_Qualities)
        self.pushButton_7.clicked.connect(self.Browse3)
        self.pushButton_9.clicked.connect(self.download_playlist)
        self.pushButton_8.clicked.connect(self.open_file_location3)
        self.pushButton_12.clicked.connect(self.open_video)
        self.comboBox_2.currentIndexChanged.connect(self.Action_Happened)
        self.comboBox_3.currentIndexChanged.connect(self.Action_Happened)
        self.comboBox_4.currentIndexChanged.connect(self.Action_Happened)

    def onDataChanged(self, progress, downloaded, speed, remain):
        self.progressBar.setValue(progress)
        self.label_8.setText("Downloaded: " + downloaded)
        self.label_38.setText("Speed: " + speed)
        self.label_39.setText("Remaining Time: " + remain)

    def Start(self):
        directory = os.path.expanduser("~") + "\AppData\Local\Temp\pySmartDL"
        if not os.path.exists(directory):
            os.makedirs(directory)
        params = {"url": self.lineEdit.text(),
                  "save_location": self.lineEdit_2.text()}
        self.download.setParams(params)
        self.download.setState(DownloadThread.Started)
        self.download.start()

    def Pause(self):
        if self.pushButton_13.text() == "Pause Downloading":
            self.download.setState(DownloadThread.Paused)
            self.pushButton_13.setText("Resume Downloading")
        elif self.pushButton_13.text() == "Resume Downloading":
            self.download.setState(DownloadThread.Resume)
            self.pushButton_13.setText("Pause Downloading")

    def Stop(self):
        self.download.setState(DownloadThread.Stopped)
        self.progressBar.setValue(0)

    def errorDownload(self):
        QMessageBox.warning(self, "Download Error", "Download Failed")

    def successfulDownload(self):
        QMessageBox.information(self, "Download Completed", "Your Download is Completed")


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    app.exec_()


if __name__ == '__main__':
    main()
