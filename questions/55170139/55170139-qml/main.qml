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
    	var pdfjs_path = Qt.resolvedUrl("3rdParty/pdfjs-%1-dist/web/viewer.html".arg("2.1.266"))
    	var path = Qt.resolvedUrl("example.pdf");
    	var url = pdfjs_path + "?file=%1".arg(path)
    	console.log(url)
    	webview.url = url
    }
}
