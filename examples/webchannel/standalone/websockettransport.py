from PyQt5 import QtCore, QtWebChannel
import json

class WebSocketTransport(QtWebChannel.QWebChannelAbstractTransport):
    def __init__(self, socket):
        super(WebSocketTransport, self).__init__(socket)
        self.m_socket = socket
        self.m_socket.textMessageReceived.connect(self.textMessageReceived)
        self.m_socket.disconnected.connect(self.deleteLater)

    def sendMessage(self, message):
        print(message)
        doc = QtCore.QJsonDocument(message)
        self.m_socket.sendTextMessage(doc.toJson(QtCore.QJsonDocument.Compact).data().decode('utf-8'))

    # @QtCore.pyqtSlot(str)
    def textMessageReceived(self, messageData):
        pass
        # message = QtCore.QJsonDocument(eval(messageData))
        """error = QtCore.QJsonParseError()
        message = QtCore.QJsonDocument.fromJson(messageData.encode(), error)
        if error.error:
            print(
                "Failed to parse text message as JSON object:",
                messageData,
                "Error is",
                error.errorString(),
            )
            return
        elif not message.isObject():
            print("Received JSON message that is not an object: ", messageData)
            return"""

        # self.messageReceived.emit(json.loads(messageData), self)

        # self.messageReceived.emit(message.object(), self)

    def __del__(self):
        self.m_socket.deleteLater()
