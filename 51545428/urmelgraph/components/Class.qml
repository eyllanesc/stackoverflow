import QtQuick 2.11
import QtQuick.Layouts 1.11

Rectangle {
    width: 50
    height: 20
    color: "#2980B9"

    border.color: "#ECF0F1"

    property string className

    Drag.active: dragArea.drag.active

    MouseArea {
        id: dragArea
        anchors.fill: parent

        drag.target: parent
        // disable delay when moved
        drag.threshold: 0
    }
    Text {
        text: className
    }
}