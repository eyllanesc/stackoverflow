import os

from PyQt5 import (
    QtCore,
    QtGui,
    QtWidgets,
    QtNetwork,
    QtWebSockets,
    QtWebChannel,
)

from core import Core
from dialog import Dialog
from websocketclientwrapper import WebSocketClientWrapper


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)

    jsFileInfo = QtCore.QFileInfo(
        os.path.join(QtCore.QDir.currentPath(), "qwebchannel.js")
    )

    if not jsFileInfo.exists():
        QtCore.QFile.copy(
            ":/qtwebchannel/qwebchannel.js", jsFileInfo.absoluteFilePath()
        )

    server = QtWebSockets.QWebSocketServer(
        "QWebChannel Standalone Example Server",
        QtWebSockets.QWebSocketServer.NonSecureMode,
    )
    if not server.listen(QtNetwork.QHostAddress.LocalHost, 12345):
        print("Failed to open web socket server.")
        sys.exit(-1)

    clientWrapper = WebSocketClientWrapper(server)
    channel = QtWebChannel.QWebChannel()
    clientWrapper.clientConnected.connect(channel.connectTo)

    dialog = Dialog()

    core = Core(dialog)
    channel.registerObject("core", core)

    file = os.path.join(
        os.path.dirname(os.path.realpath(__file__)), "index.html"
    )
    url = QtCore.QUrl.fromLocalFile(file)
    QtGui.QDesktopServices.openUrl(url)

    dialog.displayMessage(
        dialog.tr(
            "Initialization complete, opening browser at %s."
            % (url.toDisplayString(),)
        )
    )
    dialog.show()

    sys.exit(app.exec_())
