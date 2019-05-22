import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

import foo 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TreeModel {
        id: treemodel
        roles: ["phrase"]
        TreeElement{
            property string phrase: "Hey"
            TreeElement{
                property string phrase: "What's"
                TreeElement{
                    property string phrase: "Up?"
                }
            }
        }
    }
    TreeView {
        anchors.fill: parent
        model: treemodel
        TableViewColumn {
            title: "Name"
            role: "phrase"
            width: 200
        }
    }
}
