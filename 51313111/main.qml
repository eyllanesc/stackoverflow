import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebSockets 1.1
import QtWebView 1.1
import QtWebChannel 1.0
import com.eyllanesc.org 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    WebView {
        url: "qrc:/index.html"
        anchors.fill: parent
    }

    QtObject {
        id: someObject
        property string someProperty: "prop"
        WebChannel.id: "core"
        function receiveText(text){
            console.log("receiveText: ", text)
        }
        signal sendText(string text)
    }

    WebSocketTransport{
        id: transport
    }

    WebSocketServer {
        listen: true
        port: 12345
        onClientConnected: {
            if(webSocket.status === WebSocket.Open){
                channel.connectTo(transport)
                webSocket.onTextMessageReceived.connect(transport.textMessageReceive)
                transport.onMessageChanged.connect(webSocket.sendTextMessage)
            }
        }
    }

    WebChannel {
        id: channel
        registeredObjects: [someObject]
    }

    // testing
    Timer{
        interval: 500
        running: true
        repeat: true
        onTriggered: someObject.sendText(Qt.formatTime(new Date(), "hh:mm:ss") + " from QML")
    }
}
