import QtQuick 2.9
import QtQuick.Window 2.2

import QtWebView 1.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    WebView {
        id: webview
        anchors.fill: parent
        Component.onCompleted: {
            //loadHtml(htmlText, "http://index.html")
            var xhr = new XMLHttpRequest;
            xhr.open("GET", "qrc:/index.html");
            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                      loadHtml(xhr.responseText, "http://index.html");
                }
            }
            xhr.send();
        }
    }
}
