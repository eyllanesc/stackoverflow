from PyQt5 import QtCore, QtWidgets

from mainwindow import MainWindow

if __name__ == '__main__':
    import sys
    QtCore.QCoreApplication.setOrganizationName("QtExamples");
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QtWidgets.QApplication(sys.argv)
    url = QtCore.QUrl()
    if len(sys.argv) > 1:
    	url = QtCore.QUrl.fromUserInput(sys.argv[1])
    else:
    	url = QtCore.QUrl("http://www.google.com/ncr")
    browser = MainWindow(url)
    browser.resize(1024, 768)
    browser.show()
    sys.exit(app.exec_())