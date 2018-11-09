import QtQuick 2.6
import QtQuick.Window 2.2
import SerialPortLib 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Test")

    SerialPort{
        onOil_pressure_voltChanged: {
            tx.text = "%1".arg(oil_pressure_volt);
        }
    }

    Text {
        id: tx
        anchors.fill: parent
        font.family: "Helvetica"
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
