import os
import json
from functools import partial
from PyQt5 import QtCore, QtGui, QtWidgets
import utils


dir_path = os.path.dirname(os.path.abspath(__file__))
icons_dir = os.path.join(dir_path, 'assets', 'icons')


class ScrapyWorker(QtCore.QObject):
    logChanged = QtCore.pyqtSignal(str)
    started = QtCore.pyqtSignal()
    finished = QtCore.pyqtSignal()

    def __init__(self, parent=None):
        super(ScrapyWorker, self).__init__(parent)
        self._process = QtCore.QProcess(self)
        self._process.setProcessChannelMode(QtCore.QProcess.MergedChannels)
        self._process.readyReadStandardOutput.connect(self.on_readyReadStandardOutput)
        self._process.started.connect(self.started)
        self._process.finished.connect(self.finished)

    def run(self, project, program, arguments):
        self._process.setWorkingDirectory(project)
        self._process.setProgram('scrapy')
        self._process.setArguments(arguments)
        self._process.start()

    @QtCore.pyqtSlot()
    def on_readyReadStandardOutput(self):
        data = self._process.readAllStandardOutput().data().decode()
        self.logChanged.emit(data)

    @QtCore.pyqtSlot()
    def stop(self):
        self._process.kill()

class LocationWidget(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(LocationWidget, self).__init__(parent)
        self.lay = QtWidgets.QVBoxLayout(self)
        self.lay.setContentsMargins(0, 0, 0, 0)
        self.lay.addStretch()
        self.setContentsMargins(0, 0, 0, 0)
        self.widgets = []
        self.create_row()

    def create_row(self):
        widget = QtWidgets.QWidget()
        widget.setContentsMargins(0, 0, 0, 0)
        hlay = QtWidgets.QHBoxLayout(widget)
        hlay.setContentsMargins(0, 0, 0, 0)
        lineedit = QtWidgets.QLineEdit()
        button = QtWidgets.QToolButton(clicked=self.on_clicled)
        button.setFocusPolicy(QtCore.Qt.NoFocus)
        hlay.addWidget(lineedit)
        hlay.addWidget(button)
        button.setIconSize(QtCore.QSize(24, 24))
        button.setIcon(QtGui.QIcon(os.path.join(icons_dir, 'add.png')))
        self.widgets.append(widget)
        self.lay.insertWidget(-1, widget)

    @QtCore.pyqtSlot()
    def on_clicled(self):
        button = self.sender()
        widget = button.parentWidget()
        if self.lay.indexOf(widget) == (self.lay.count()-1):
            self.create_row()
        else:
            self.lay.removeWidget(widget)
            widget.deleteLater()
            self.widgets.remove(widget)
        for widget in self.widgets:
            button = widget.findChild(QtWidgets.QToolButton)
            button.setIcon(QtGui.QIcon(os.path.join(icons_dir, 'remove.png')))
        self.widgets[-1].findChild(QtWidgets.QToolButton).setIcon(QtGui.QIcon(os.path.join(icons_dir, 'add.png')))

    def get_locations(self):
        locations = []
        for widget in self.widgets:
            le = widget.findChild(QtWidgets.QLineEdit)
            if le.text():
                locations.append(le.text())
        return locations

class YellowWidget(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super(YellowWidget, self).__init__(parent)
        self.setWindowTitle('Yellow Pages Scrapper')
        self.scrapy_worker = ScrapyWorker(self)
        self.search_item_le = QtWidgets.QLineEdit()
        self.location_widget = LocationWidget()
        self.start_stop_button = QtWidgets.QPushButton("Start", checkable=True)
        self.text_edit = QtWidgets.QTextBrowser()

        central_widget = QtWidgets.QWidget()
        self.setCentralWidget(central_widget)
        lay = QtWidgets.QGridLayout(central_widget)
        lay.addWidget(QtWidgets.QLabel("<b>Search:</b>"), 0, 0)
        lay.addWidget(self.search_item_le, 0, 1)
        lay.addWidget(QtWidgets.QLabel("<b>Locations:</b>"), 1, 0, alignment=QtCore.Qt.AlignTop|QtCore.Qt.AlignLeft)
        lay.addWidget(self.location_widget, 1, 1, alignment=QtCore.Qt.AlignTop)
        lay.addWidget(self.start_stop_button, 2, 0, 1, 2)
        lay.addWidget(self.text_edit, 3, 0, 1, 2)

        self.start_stop_button.toggled.connect(self.on_checked)
        self.scrapy_worker.logChanged.connect(self.insert_log)
        self.scrapy_worker.started.connect(self.text_edit.clear)
        self.scrapy_worker.finished.connect(partial(self.start_stop_button.setChecked, False))

    @QtCore.pyqtSlot(bool)
    def on_checked(self, state):
        if state:
            # crapy crawl yellow -a parameters='{"search_item": "house", "locations": ["usa", "germany"]}'
            search_item = self.search_item_le.text()
            locations = self.location_widget.get_locations()
            directory, program, args = utils.create_arguments(search_item, locations)
            self.scrapy_worker.run(directory, program, args)
            self.start_stop_button.setText('Stop')
        else:
            self.start_stop_button.setText('Start')
            self.scrapy_worker.stop()

    @QtCore.pyqtSlot(str)
    def insert_log(self, text):
        prev_cursor = self.text_edit.textCursor()
        self.text_edit.moveCursor(QtGui.QTextCursor.End)
        self.text_edit.insertPlainText(text)
        self.text_edit.setTextCursor(prev_cursor)

if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    app.setStyle('fusion')
    w = YellowWidget()
    w.resize(640, 480)
    w.show()
    sys.exit(app.exec_())