import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 180; height: 200

        Component {
            id: contactDelegate
            Item {
                width: 180; height: 40
                Column {
                    Text { text: '<b>Name:</b> ' + name }
                    Text { text: '<b>Number:</b> ' + number }
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked:  {
                        var pos = mapToItem(listView, 0, height)
                        menu.x = pos.x
                        menu.y = pos.y
                        menu.open()
                    }
                }
            }
        }

        ListView {
            id: listView
            objectName: "list"
            anchors.fill: parent
            model: ContactModel{}
            delegate: contactDelegate
            focus: true

            Menu {
                id: menu
                MenuItem { text: "item1" }
                MenuItem { text: "item2"; }
                MenuItem { text: "item3"; }
            }

        }
    }
}
