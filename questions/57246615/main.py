import os
import sys
from PyQt5 import QtCore, QtWidgets, QtWebEngineWidgets


CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))
viewer_path = os.path.join(CURRENT_DIR, "3rdParty", "pdfjs-2.1.266-dist/web/viewer.html")


class Widget(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(Widget, self).__init__(parent)

        button = QtWidgets.QPushButton("Load PDF", clicked=self.onClicked)
        self.viewer = QtWebEngineWidgets.QWebEngineView()

        lay = QtWidgets.QVBoxLayout(self)
        lay.addWidget(button)
        lay.addWidget(self.viewer)
        self.resize(640, 480)

    @QtCore.pyqtSlot()
    def onClicked(self):
        filename, _ = QtWidgets.QFileDialog.getOpenFileName(
            self, self.tr("Open PDF"), CURRENT_DIR, self.tr("PDF Files (*.PDF)")
        )
        if filename:
            self.load_pdf(filename)

    def load_pdf(self, filename):
        url_viewer = QtCore.QUrl.fromLocalFile(viewer_path)
        query = QtCore.QUrlQuery()
        query.addQueryItem("file", "file:///{}".format(filename))
        url_viewer.setQuery(query)
        self.viewer.load(url_viewer)


if __name__ == "__main__":
    import sys

    # sys.argv.append("--disable-web-security")
    app = QtWidgets.QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())
