import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: main_window
    width: 640
    height: 480
    visible: true

    Item {
        id: rect_parent
        objectName: "rect_parent_object"
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        transform: Translate {x: -20; y: -30}

        Rectangle {
            id: rect
            objectName: "rect_object"
            x: parent.width/2
            y: parent.height/2
            width: parent.width/3
            height: parent.height/3
            color: "red"
        }
    }
}
