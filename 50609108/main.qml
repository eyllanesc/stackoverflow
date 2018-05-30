import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextField {
        id: serverField1
        x: 15
        y: 46
        width: 120
        height: 45
        topPadding: 8
        font.pointSize: 14
        bottomPadding: 16
        placeholderText: "Server Ip"
        renderType: Text.QtRendering
        onTextChanged: backend.text = text
    }
}
