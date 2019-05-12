import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {text: qsTr("Open...")}
            MenuItem {text: qsTr("Close")}
        }
        Menu {
            title: qsTr("Language")
            MenuItem {
                text: qsTr("English")
                onTriggered: trans.selectLanguage("en")

            }
            MenuItem {
                text: qsTr("Spanish")
                onTriggered: trans.selectLanguage("es")
            }
        }
    }
    Button{
        anchors.centerIn: parent
        text: qsTr("button")
    }
}
