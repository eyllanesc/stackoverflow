import sys
import os

import branca
from PyQt5.QtCore import QMetaObject, QUrl, pyqtSlot, QDir
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWebEngineWidgets import QWebEngineSettings, QWebEngineView
from PyQt5.QtWidgets import QMainWindow, QWidget, QGridLayout, QApplication
from branca.element import *

import folium


class Example(QMainWindow):
    htmlPath = QDir.current()
    htmlPath.cd("html")
    def __init__(self):
        super().__init__()

        self.setObjectName('Main')
        QMetaObject.connectSlotsByName(self)

        self.view = QWebEngineView()
        self.view.settings().setAttribute(QWebEngineSettings.LocalStorageEnabled, True)
        self.view.setObjectName('MapWidget')

        self.window = QWidget()
        self.window.setObjectName('MainWidget')
        self.layout = QGridLayout(self.window)
        self.layout.addWidget(self.view)
        self.setCentralWidget(self.window)

        self.channel = QWebChannel(self.view.page())
        self.view.page().setWebChannel(self.channel)
        self.channel.registerObject("jshelper", self)

        principal = Figure()
        js = JavascriptLink(QUrl.fromLocalFile(self.htmlPath.absoluteFilePath("qwebchannel.js")).toString())
        principal.header.add_child(Element(js.render()))
        map = folium.Map(location=[36, -108],
                             zoom_start=5, tiles='StamenWatercolor').add_to(principal)
        fastestRoute = folium.PolyLine(((40, -110), (50, -110)),
                                       weight=5, color='blue').add_to(map)

        f = Figure()
        f.html.add_child(Element('<button id="myBtn">Try it</button>'))
        f.html.add_child(Element('<p>\n TEST \n</p>'))

        link = JavascriptLink(QUrl.fromLocalFile(self.htmlPath.absoluteFilePath("popup.js")).toString())
        f.html.add_child(Element(link.render()))

        iframe = branca.element.IFrame(html=f.render(), width=500, height=300)
        popup = folium.Popup(iframe, max_width=500)
        fastestRoute.add_child(popup)

        principal.save(self.htmlPath.absoluteFilePath("test.html"))
        self.view.load(QUrl().fromLocalFile(self.htmlPath.absoluteFilePath("test.html")))
        self.setGeometry(100, 100, 1200, 900)
        self.show()

    @pyqtSlot(str)
    def pathSelected(self, lat):
        print(lat)


if __name__ == '__main__':
    sys.argv.append("--remote-debugging-port=8000")
    sys.argv.append("--disable-web-security")
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
