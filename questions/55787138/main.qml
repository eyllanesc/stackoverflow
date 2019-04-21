import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import Qt.labs.settings 1.0
import Qt.labs.platform 1.0 as Platform

import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 1040
    height: 480
    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        Button {
            text: qsTr("Update List Model")
            onClicked: myModel.addPerson()
        }
        TableView {
            width: 400
            height: 200
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            ScrollIndicator.horizontal: ScrollIndicator { }
            ScrollIndicator.vertical: ScrollIndicator { }
            model: myModel
            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                border.color: "black"
                border.width: 2
                color: heading ? 'teal':"green"
                TableView.onPooled: console.log(tabledata + " pooled")
                TableView.onReused: console.log(tabledata + " resused")

                Text {
                    text: tabledata
                    font.pointSize: 10
                    anchors.centerIn: parent
                }
            }
        }
    }
}
