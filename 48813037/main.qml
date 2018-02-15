import QtQuick 2.9
import QtQuick.Window 2.2

import com.eyllanes.items 1.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyQuickItem {
        id: mitem
        property color nextColor
        onNextColorChanged: {
            console.log("The next color will be: " + nextColor.toString())
        }
    }

    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: mitem.nextColor = Qt.rgba( Math.random() % 256, Math.random() % 256, Math.random() % 256)
    }
}
