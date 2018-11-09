import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TableView {
        id: tableView2
        anchors.fill: parent
        TableViewColumn {
            title: "Parameter Name"
            role: "one"
        }
        TableViewColumn {
            title: "Value"
            role: "two"
            delegate: myDelegate
        }
        model: myTestModel
    }

    Component {
        id: myDelegate
        Loader {
            property var roleTwo: model.two
            sourceComponent: typeof(roleTwo)=='boolean'? checkBoxDelegate: stringDelegate
        }
    }

    Component {
        id: checkBoxDelegate
        CheckBox{
            checked: roleTwo
            onCheckedChanged:{
                var pos = mapToGlobal(0, 0)
                var p = tableView2.mapFromGlobal(pos.x, pos.y)
                var row = tableView2.rowAt(p.x, p.y)
                if(row >= 0)
                    myTestModel.updateValue(tableView2.row, checked, "two")
            }
        }
    }

    Component {
        id: stringDelegate
        TextField {
            text: roleTwo
            onEditingFinished: {
                var pos = mapToGlobal(0, 0)
                var p = tableView2.mapFromGlobal(pos.x, pos.y)
                var row = tableView2.rowAt(p.x, p.y)
                if(row >= 0)
                    myTestModel.updateValue(tableView2.row, text, "two")
            }

        }
    }
}
