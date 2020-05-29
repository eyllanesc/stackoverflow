import QtQuick 2.14
import QtQuick.Window 2.14
import QtMultimedia 5.14

import Application.CameraService 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    VideoOutput {
        objectName: "videoOutput";
        anchors.fill: parent;
        fillMode: VideoOutput.PreserveAspectCrop;
        source: CameraService;
    }
}
