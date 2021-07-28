import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Title")

    ListModel {
        id: list_model

        ListElement {
            name: QT_TR_NOOP("house")
        }

        ListElement {
            name: QT_TR_NOOP("table")
        }

        ListElement {
            name: QT_TR_NOOP("chair")
        }

    }

    ColumnLayout {
        anchors.fill: parent

        ComboBox {
            model: translator ? translator.languages : null
            textRole: "display"
            Layout.fillWidth: true
            onActivated: function(index) {
                translator.set_language(currentText);
            }
        }

        Button {
            text: qsTr("name")
            Layout.fillWidth: true
        }

        ListView {
            model: list_model
            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: Text {
                text: qsTr(name)
            }

        }

    }

}
