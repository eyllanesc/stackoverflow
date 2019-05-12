import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.6

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Wipeout viewer")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Language")
            MenuItem {
                text: qsTr("&English")
                onTriggered: translator.setLanguage("en")
            }
            MenuItem {
                text: qsTr("&French")
                onTriggered: translator.setLanguage("fr")
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&About")
            }
        }
    }
}
