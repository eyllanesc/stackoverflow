import QtQuick 2.6
import QtQuick.Controls 2.0 as QQC2
import Interfacage 1.0

Rectangle {
    width: 800
    height: 800
    color: "white"

    ListModel {
        id: appModel
        ListElement {
            name: "Contacts"
            icon: "pics/Resources/AddressBook_48.png"
        }
        ListElement {
            name: "Music"
            icon: "pics/Resources/AudioPlayer_48.png"
        }
        ListElement {
            name: "Movies"
            icon: "pics/Resources/VideoPlayer_48.png"
        }
        ListElement {
            name: "Camera"
            icon: "pics/Resources/Camera_48.png"
        }
        ListElement {
            name: "Calendar"
            icon: "pics/Resources/DateBook_48.png"
        }
        ListElement {
            name: "Todo List"
            icon: "pics/Resources/TodoList_48.png"
        }
    }

    Component {
        id: appDelegate
        Item {
            width: 100
            height: 100
            scale: PathView.iconScale

            /*Image {
                id: myIcon
                y: 20
                anchors.horizontalCenter: parent.horizontalCenter
                source: icon
            }*/
            Text {
                anchors {
                    //top: myIcon.bottom
                    horizontalCenter: parent.horizontalCenter
                }
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = index
                    InterfacageQML.mouseClick()
                }
            }
        }
    }

    Component {
        id: appHighlight
        Rectangle {
            width: 100
            height: 80
            color: "lightsteelblue"
        }
    }

    PathView {
        id: view
        anchors.fill: parent
        highlight: appHighlight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: appModel
        delegate: appDelegate
        path: Path {
            startX: 50
            startY: 80
            PathAttribute {
                name: "iconScale"
                value: 2.0
            }
            PathQuad {
                x: 250
                y: 200
                controlX: 50
                controlY: 200
            }
            PathAttribute {
                name: "iconScale"
                value: 2.0
            }
            PathQuad {
                x: 600
                y: 50
                controlX: 400
                controlY: 200
            }
            PathAttribute {
                name: "iconScale"
                value: 2.0
            }
        }
    }
}
