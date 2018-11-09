import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3


Window {
    id:app
    visible: true
    width: 480
    height: 800
    title: qsTr("Hello World")

    ListView {

        model: myForms
        anchors.fill: parent
        delegate:  ColumnLayout{
            spacing: 30
            Text{
                text: nameForm
                font.pointSize:20
                color: "red"
                font.capitalization: Font.Capitalize
            }
            GridView {
                id:gr
                width: 300; height: 300
                cellWidth: 100 ; cellHeight: 100
                model: grid // grid.length
                delegate: Item{
                    width : gr.cellWidth
                    height: gr.cellHeight
                    Rectangle{
                        anchors.centerIn: parent
                        width:parent.width-10
                        height: parent.height-10
                        color: grid[index].color
                        Text {
                            id: name
                            anchors.fill: parent
                            text: grid[index].name
                        }
                    }

                }

            }
        }
    }

}
