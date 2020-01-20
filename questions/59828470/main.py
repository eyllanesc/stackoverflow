import os
import sys

from PyQt5 import QtCore, QtGui, QtQuick, QtWidgets

DIR_PATH = os.path.dirname(os.path.realpath(__file__))
ICON_DIR = os.path.join(DIR_PATH, "icons")


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)

        central_widget = QtWidgets.QWidget()
        self.setCentralWidget(central_widget)

        lay = QtWidgets.QHBoxLayout(central_widget)

        lay.addWidget(QtWidgets.QLabel("QLabel", alignment=QtCore.Qt.AlignCenter))

        file = os.path.join(DIR_PATH, "gallery.qml")
        self.view = QtQuick.QQuickView()
        self.view.statusChanged.connect(self.on_statusChanged)
        self.view.setResizeMode(QtQuick.QQuickView.SizeRootObjectToView)
        engine = self.view.engine()
        context = engine.rootContext()
        context.setContextProperty("availableStyles", availableStyles())
        self.view.setSource(QtCore.QUrl.fromLocalFile(file))
        widget = QtWidgets.QWidget.createWindowContainer(self.view)
        lay.addWidget(widget)

    def on_statusChanged(self, status):
        if status == QtQuick.QQuickView.Error:
            for error in self.view.errors():
                print(error.toString())
            sys.exit(-1)


def availableStyles():
    # https://github.com/qt/qtquickcontrols2/blob/5.14/src/quickcontrols2/qquickstyle.cpp#L591

    importPaths = [
        QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.Qml2ImportsPath),
        ":/qt-project.org/imports",
        QtCore.QCoreApplication.applicationDirPath(),
        DIR_PATH,
    ]
    path = os.environ.get("QT_QUICK_CONTROLS_STYLE_PATH", "")
    if path:
        importPaths.append(path)

    stylePaths = []
    targetPath = "QtQuick/Controls.2"
    for importPath in importPaths:
        d = QtCore.QDir(importPath)
        if d.cd(targetPath):
            stylePaths.append(d.absolutePath())

    styles = []
    for path in stylePaths:
        entries = QtCore.QDir(path).entryInfoList(
            QtCore.QDir.Dirs | QtCore.QDir.NoDotAndDotDot
        )
        for entry in entries:
            name = entry.fileName()
            if not name.endswith(".dSYM") and name != "designer":
                # print(path, name)
                styles.append(name)
    return list(set(styles))


def main():

    QtCore.QCoreApplication.setApplicationName("Gallery")
    QtCore.QCoreApplication.setOrganizationName("QtProject")
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QtWidgets.QApplication(sys.argv)

    QtGui.QIcon.setThemeSearchPaths(QtGui.QIcon.themeSearchPaths() + [ICON_DIR])
    QtGui.QIcon.setThemeName("gallery")

    default_style = "Material"

    settings = QtCore.QSettings()
    style = settings.value("style")
    if not style:
        style = default_style
        settings.setValue("style", style)

    os.environ["QT_QUICK_CONTROLS_STYLE"] = style

    w = MainWindow()
    w.showMaximized()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
