import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image {
        property int number
        id: name
        source: "image://numbers/"+number

        NumberAnimation on number {
            from:0
            to: 60
            duration: 1000
        }
    }
}
