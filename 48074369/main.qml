import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import org.example 1.0

ApplicationWindow {
    id: head
    visible: true
    title: qsTr("Hello World")
    width:  Screen.width
    height: Screen.height

    DrawItem
    {
        id: draw_on_qimage
        anchors.fill: parent
        font.pointSize: Math.min(head.height/10, head.width/10)
        transform: Scale {
            xScale: head.width / 640
            yScale: head.height / 480
        }
    }
}
