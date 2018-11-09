import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: card
    Layout.fillWidth: true
    Layout.fillHeight: true

    property alias backImageSource: backImage.source
    property alias flipped: flipable.flipped
    property alias state: flipable.state
    signal finished()

    Flipable {
        id: flipable
        anchors.fill: parent
        property alias backImageSource: backImage.source

        property bool flipped: false

        front: Rectangle {
            anchors.fill: parent
            color: '#965555'
            radius: 12
            border.width: 2
            border.color: '#ffffff'

            Image {
                anchors { fill: parent; centerIn: parent }
                fillMode: Image.PreserveAspectFit
                source: 'qrc:/images/back.gif'
            }
        }

        back: Rectangle {
            anchors.fill: parent
            color: '#965555'
            radius: 12
            border.width: 2
            border.color: '#ffffff'

            Image {
                id: backImage
                width: parent.width - 25
                height: parent.height - 25
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width / 2
            origin.y: flipable.height / 2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

        states: [
            State {
                name: 'back'
                PropertyChanges { target: rotation; angle: 180 }
                when: flipable.flipped
            },
            State {
                name: 'remove'
                PropertyChanges {
                    target: card
                    visible: false
                }
            }
        ]

        transitions: Transition {
            NumberAnimation { target: rotation; property: 'angle'; duration: 400 }
            onRunningChanged: {
                if ((state == "back") && (!running))
                    finished()
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: card.flipped = true
        }
    }
}
