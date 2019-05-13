from PyQt5 import QtCore, QtWidgets, QtWebEngineWidgets


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.m_view = QtWebEngineWidgets.QWebEngineView()
        self.setCentralWidget(self.m_view)
        page = self.m_view.page()
        page.featurePermissionRequested.connect(
            self.on_featurePermissionRequested
        )

        page.load(QtCore.QUrl("https://maps.google.com"))

    @QtCore.pyqtSlot(QtCore.QUrl, QtWebEngineWidgets.QWebEnginePage.Feature)
    def on_featurePermissionRequested(self, securityOrigin, feature):
        if feature != QtWebEngineWidgets.QWebEnginePage.Geolocation:
            return
        msgBox = QtWidgets.QMessageBox(self)
        msgBox.setText(
            self.tr("{} wants to know your location").format(
                securityOrigin.host()
            )
        )
        msgBox.setInformativeText(
            self.tr(
                "Do you want to send your current location to this website?"
            )
        )
        msgBox.setStandardButtons(
            QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No
        )
        msgBox.setDefaultButton(QtWidgets.QMessageBox.Yes)

        page = self.m_view.page()

        if msgBox.exec_() == QtWidgets.QMessageBox.Yes:
            print("Yes")
            page.setFeaturePermission(
                securityOrigin,
                feature,
                QtWebEngineWidgets.QWebEnginePage.PermissionGrantedByUser,
            )
        else:
            page.setFeaturePermission(
                securityOrigin,
                feature,
                QtWebEngineWidgets.QWebEnginePage.PermissionDeniedByUser,
            )


if __name__ == "__main__":
    import sys

    QtCore.QCoreApplication.setOrganizationName("QtExamples")
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QtWidgets.QApplication(sys.argv)

    mainWindow = MainWindow()
    mainWindow.resize(1024, 768)
    mainWindow.show()

    sys.exit(app.exec_())
