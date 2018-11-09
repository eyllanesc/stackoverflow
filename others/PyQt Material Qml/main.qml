import QtQuick 2.3
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1    

ApplicationWindow{
    title: qsTr('Qml app')
    id: mainWindow
    width:  480
    height: 640
    visible: true
    Material.theme: Material.Light
    Material.accent: Material.Purple

    Column {
        anchors.centerIn: parent

        RadioButton { text: qsTr("Small") }
        RadioButton { text: qsTr("Medium");  checked: true }
        RadioButton { text: qsTr("Large") }

        Button {
            text: qsTr("Button")
            highlighted: true
            Material.accent: Material.Orange
        }
        Button {
            text: qsTr("Button")
            highlighted: true
            Material.background: Material.Teal
        }

        Pane {
            width: 120
            height: 120

            Material.elevation: 6

            Label {
                text: qsTr("I'm a card!")
                anchors.centerIn: parent
            }
        }

        Button {
            text: qsTr("Button")
            Material.foreground: Material.Pink
        }

        Pane {
            Material.theme: Material.Dark

            Button {
                text: qsTr("Button")
            }
        }

        Rectangle {
            color: Material.color(Material.Red)
        }
   	} 
}