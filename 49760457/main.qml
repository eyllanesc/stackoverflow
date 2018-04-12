import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Test")

    Scene
    {
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
    }
}
