from PyQt5 import QtCore, QtWebSockets

from websockettransport import WebSocketTransport


class WebSocketClientWrapper(QtCore.QObject):
    clientConnected = QtCore.pyqtSignal(WebSocketTransport)

    def __init__(self, server, parent=None):
        super(WebSocketClientWrapper, self).__init__(parent)
        self.m_server = server

        self.m_server.newConnection.connect(self.handleNewConnection)

    @QtCore.pyqtSlot()
    def handleNewConnection(self):
        self.clientConnected.emit(
            WebSocketTransport(self.m_server.nextPendingConnection())
        )
