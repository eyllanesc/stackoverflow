import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TreeView{
        anchors.fill: parent

        model: qjsonmodel
        TableViewColumn{
            title:"Key"
            role: "keyData"
        }
        TableViewColumn{
            title:"Role"
            role: "valueData"
        }
    }
}
