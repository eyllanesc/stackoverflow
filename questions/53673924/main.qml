import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
ApplicationWindow {
    id: root
    width: 800
    minimumWidth: 500
    height: 600
    minimumHeight: 600
    visible: true
    title: "Translating QML application"

    Column {
        width: parent.width * 0.95
        spacing: 15
        padding: 15
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater{
                model: trans.languages
                Button{
                    id: btn
                    property string code: modelData
                    text: trans.languageByCode(code)
                    onClicked: trans.selectLanguage(btn.code)
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    highlighted: code == trans.currentLanguage
                }
            }
        }
        Label {
            font.pixelSize: 16
            text: qsTr("I woke up after midnight and realised - <b>IT DOES</b>!<br/>"
                       + "Everything goes according to the plan.")
        }
    }
}
