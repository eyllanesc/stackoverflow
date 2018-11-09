import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Canvas {
        id:canvas
        anchors.fill: parent
        onPaint:{
            var ctx = canvas.getContext('2d');
            ctx.lineWidth = 4
            ctx.fillStyle = "orange"
            ctx.strokeStyle = "red"
            ctx.fillRect(50, 40, 100, 100)
            ctx.stroke()
            ctx.fill()

            ctx.lineWidth = 10
            ctx.fillStyle = colorProvider.color
            ctx.fillRect(150, 150, 300, 300)
            ctx.stroke()
            ctx.fill()

            ctx.roundedRect(20, 20, 40, 40, 10, 10)
        }
    }

    Connections {
        target: colorProvider
        onColorChanged: canvas.requestPaint()
    }
}
