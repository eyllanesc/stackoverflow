import QtQuick 2.0
import "."

Rectangle
{
    id: scene
    anchors.fill: parent
    width: parent.width * 0.5
    height: width
    color: "grey"
    Text
    {
        text: Style.qW
        anchors.centerIn: parent
        font.bold: true
        font.pointSize: 20
        fontSizeMode: Text.Fit
        color: "white"
    }

    Component.onCompleted:
    {
        //console.log(Style.qW)
    }
}
