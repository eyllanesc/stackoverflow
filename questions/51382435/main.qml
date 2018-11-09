import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GridView {
        id: gv
        anchors.fill: parent
        model: manager.filterModel
        delegate:
            Image {
            width: 100
            height: 100
            source: "image://model/"+item.uuid
        }
    }
}
