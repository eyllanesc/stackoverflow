import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id: qInterfaceList
        anchors.fill: parent
        model: myModel
        orientation: ListView.Vertical
        delegate:
            Rectangle {
                height: 30;
                width: 120;
                border.color: "red"
                border.width: 3
            }
    }
    Component.onCompleted: console.log(myModel)
}
