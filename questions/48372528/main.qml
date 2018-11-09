import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.MyApp.qml 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ComboBox {
        model: serial.availablePorts()
    }
    SerialPortManager {
        id: serial
    }
}
