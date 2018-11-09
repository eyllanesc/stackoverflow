import sys
from PyQt5 import QtWebChannel
from PyQt5.QtWidgets import *
from GUI_tmy3 import *


class ShowMap_fun(QMainWindow):
    def __init__(self):
        super().__init__()
        self.map_ui = Ui_tmy3page()  # The name of my top level object is MainWindow
        self.map_ui.setupUi(self)
        channel = QtWebChannel.QWebChannel(self.map_ui.html_code.page())
        self.map_ui.html_code.page().setWebChannel(channel)
        channel.registerObject("jshelper", self)
        self.map_ui.html_code.load(QtCore.QUrl.fromLocalFile(QtCore.QDir.current().filePath("useless.html")))

    @QtCore.pyqtSlot(float, float)
    def markerMoved(self, lat, lng):
        print(lat, lng)


if __name__ == '__main__':
    sys.argv.append("--remote-debugging-port=8000")
    app = QApplication(sys.argv)
    ex = ShowMap_fun()
    ex.show()
    sys.exit(app.exec_())
