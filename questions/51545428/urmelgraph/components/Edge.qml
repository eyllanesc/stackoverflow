import QtQuick 2.11
import CustomGeometry 1.0

StraightLine {
    property var anchor1
    property var anchor2

    anchors.fill: parent

    Component.onCompleted: {
        console.log(anchor1)
        console.log(anchor2)
    }

    p2: Qt.point(anchor2.x + (anchor2.width/2), anchor2.y + (anchor2.height/2))
    p1: Qt.point(anchor1.x + (anchor1.width/2), anchor1.y + (anchor1.height/2))
}