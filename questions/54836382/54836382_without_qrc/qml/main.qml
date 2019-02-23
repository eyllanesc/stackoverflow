import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import "Themes"

ApplicationWindow
{
    id: mainWindow
    width: 640
    height: 480
    visible: true
    color:  Theme.primaryBackgroundColor
    title: qsTr("SmartDraw")
    flags: Qt.FramelessWindowHint | Qt.Window
    header: Rectangle {
        id: windowHeader
        height: 38
        width: parent.width
        color: "#0e6afa"

        MouseArea {
            id: windowResizeUp
            height: 2
            anchors.bottom: windowDragArea.top
            anchors.left: parent.left
            anchors.right: minimize.left
            cursorShape: Qt.SizeVerCursor
            property real lastMousePosY: 0

            onPressed: {
                lastMousePosY = mouse.y
            }
            onMouseYChanged:
            {
                var dy = (mouseY - lastMousePosY)
                mainWindow.y += dy
                mainWindow.height -= dy
            }
        }

        MouseArea {
            id: windowDragArea
            height: parent.height - 2
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: minimize.left

            property point lastMousePos: Qt.point(0, 0)
            onPressed: { lastMousePos = Qt.point(mouseX, mouseY); }
            onMouseXChanged: mainWindow.x += (mouseX - lastMousePos.x)
            onMouseYChanged: mainWindow.y += (mouseY - lastMousePos.y)
        }

        Button {
            id: minimize
            width: 30
            height: parent.height
            anchors.right: maximize.left
            onClicked: mainWindow.showMinimized()

            background: Rectangle {
                width: parent.width
                height: parent.height
                color: windowHeader.color
            }

            Rectangle {
                color: "white"
                height: 2
                width: Math.round(parent.width*(2.0/3.0))
                anchors.centerIn: parent
            }
        }

        Button {
            id: maximize
            width: 30
            height: parent.height
            anchors.right: close.left
            onClicked: mainWindow.visibility == Window.Maximized ? mainWindow.showNormal() : mainWindow.showMaximized()

            background: Rectangle {
                width: parent.width
                height: parent.height
                color: windowHeader.color
            }

            Rectangle {
                color: "white"
                width: 15
                height: 15
            }
        }

        Button {
            id: close
            width: 30
            anchors.right: parent.right
            height: parent.height
            onClicked: Qt.quit()

            background: Rectangle {
                width: parent.width
                height: parent.height
                color: windowHeader.color
            }

            Text {
                color: "white"
                text: "X"
            }
        }
    }


    footer: Rectangle {
        id: windowFooter
        color: "#0e6afa"
        height: 23

        MouseArea {
            id: windowResizeBottomLeft
            width:  4
            height: 4
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            cursorShape: Qt.SizeBDiagCursor

            property point lastMousePos: Qt.point(0,0)

            onPressed: {
                lastMousePos = Qt.point(mouse.x,mouse.y)
            }

            onMouseYChanged:
            {
                var dx = (mouseX - lastMousePos.x)
                var dy = (mouseY - lastMousePos.y)

                mainWindow.x += dx
                mainWindow.width -= dx
                mainWindow.height += dy
            }
        }

        MouseArea {
            id: windowResizeDown
            x: 4
            height: 2
            anchors.bottom: parent.bottom
            anchors.left: windowResizeBottomLeft.right
            anchors.right: parent.right
            cursorShape: Qt.SizeVerCursor

            property real lastMousePosY: 0

            onPressed: {
                lastMousePosY = mouse.y
            }

            onMouseYChanged:
            {
                var dy = (mouseY - lastMousePosY)
                mainWindow.height += dy
            }
        }
    }
}
