import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick 2.0
import Foo 1.0

ApplicationWindow{
    width: 300
    height: 300
    visible: true

    Text{
        id:txt
        text: "press me to start"
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Foo{
        id: foo
        onProgressChanged: txt.text= progress
    }

    MouseArea {
        anchors.fill: parent
        onClicked: foo.run_bar()
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            ProgressBar {
                value: foo.progress
                maximumValue: 100
                anchors.fill: parent
            }
        }
    }
}
