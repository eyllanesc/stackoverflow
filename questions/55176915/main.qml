import QtQuick 2.9

Rectangle {
    color: "#00000000"
    anchors.fill: parent
    transformOrigin: Item.Center
    MouseArea {
        id: buttFArea
        anchors.fill: parent
        onClicked: flower.onClicked()
    }
}
