import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import com.example.data 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Example")

    ColumnLayout {
        anchors.centerIn: parent
        Button {
            id: button
            Layout.fillWidth: true
            text: "start"
            onClicked: data.start()
        }

        Text {
            id: text1
            text: data.number
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }

    Data{
        id: data
    }
}
