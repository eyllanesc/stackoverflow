import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebView 1.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("PDFJS Example")
    WebView{
        id: webview
        anchors.fill: parent
    }
    Component.onCompleted:{
        PDFJS.version = "2.1.266"
        webview.url = PDFJS.getUrl("file://" + applicationDirPath + "/example.pdf")
    }
}
