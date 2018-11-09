import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtWebEngine 1.4


import "testJava.js" as Helper
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    WebEngineView{

        id: webEngine
        anchors.fill: parent
        url: "TestPage.html"

        function someSlot(v) {
            console.log("Signal received "+v);
        }

        onLoadingChanged: {
            switch(loadRequest.status){
            case  WebEngineLoadRequest.LoadStartedStatus:
                console.log("LoadStartedStatus");
                Helper.internalQmlObject.someSignal.connect(someSlot);
                Helper.runNow();
                break;
            case WebEngineLoadRequest.LoadSucceededStatus:
                console.log("LoadSucceededStatus");
                break;
            case WebEngineLoadRequest.LoadFailedStatus:
                console.log("LoadFailedStatus");
                break;
            }
        }
    }
}
