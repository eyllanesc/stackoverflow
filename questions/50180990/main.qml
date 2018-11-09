import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebEngine 1.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "qrc:/html/index.html"
        profile.onDownloadRequested: downloadHelper.onDownloadRequested(download)

        onNewViewRequested: {
            var newWindow = Qt.createQmlObject('import QtQuick.Window 2.2;
                                                import QtWebEngine 1.5;
                                                 Window {
                                                    width: 640; height: 480;
                                                    visible: true;
                                                    property alias wv: wv
                                                    WebEngineView{id:wv; anchors.fill: parent}}',
                                               webView,
                                               "dynamicSnippet1");
            console.log(newWindow.wv)
            request.openIn(newWindow.wv)
        }
    }
}
