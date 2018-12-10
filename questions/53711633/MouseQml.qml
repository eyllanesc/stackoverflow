import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 500
    height: 500
    Row {
        id: tools
        Button {
            id: clear
            objectName: "clear"
            text: "Clear"
            onClicked: {
                canvas.clear()
            }
        }
    }
    Canvas {
        id: canvas
        anchors.top: tools.bottom
        width: 500
        height: 500
        property int lastX: 0
        property int lastY: 0

        function clear() {
            var ctx = getContext("2d")
            ctx.reset()
            canvas.requestPaint()
            mouse.clear()
        }
    }
}
