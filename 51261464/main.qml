import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        width: 200; height: 250
        model: modelist[0]
        delegate: Text { text: "Animal: " + type + ", " + size }
    }
}
