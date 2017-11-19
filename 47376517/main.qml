import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    color: "white"
    ListModel{
        id: websiteModel
        ListElement { name: "flower"}
        ListElement { name: "house" }
        ListElement { name: "water" }
    }

    ListView {
        id: websiteListView
        orientation: ListView.Vertical
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent
        model: websiteModel
        focus: true
        highlight: Rectangle { color: "lightsteelblue";}
        highlightFollowsCurrentItem: true
        objectName: "websiteListView"

        delegate: Component {
            Item {
                property variant itemData: model.modelData
                width: parent.width
                height: 20

                Row {
                    id: row1
                    spacing: 10
                    anchors.fill: parent

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                        MouseArea {
                            id: websiteMouseArea
                            anchors.fill: parent
                            onClicked: {
                                websiteListView.currentIndex = index
                            }
                        }
                    }
                }
            }
        }
        onCurrentIndexChanged: {
            helper.fun(currentIndex)
        }
    }
}
