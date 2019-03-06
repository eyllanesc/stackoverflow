from PyQt5 import QtCore, QtWidgets,QtWebEngineWidgets

if __name__ == '__main__':
    import sys
    
    sys.argv.append("--remote-debugging-port=8000")
    sys.argv.append("--disable-web-security")
    app = QtWidgets.QApplication(sys.argv)
    view = QtWebEngineWidgets.QWebEngineView()
    view.load(QtCore.QUrl("https://www.qt.io")) #"http://localhost:8000"))
    view.show()
    sys.exit(app.exec_())