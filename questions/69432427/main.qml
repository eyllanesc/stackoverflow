import QtQuick
import QtQuick.Window
import QtMultimedia

import com.eyllanesc.multimedia

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Producer{
        id: producer
        videoSink: videoOutput.videoSink
    }
    VideoOutput{
        id: videoOutput
        anchors.fill: parent
    }
    Component.onCompleted: producer.start()
}
