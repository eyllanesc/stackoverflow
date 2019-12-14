import QtQuick 2.9
import QtQuick.Controls 2.2

import OSC 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    
    Text {
        id: message
        anchors.centerIn: parent
    }
    OSCReceiver {
        port: 3333
        onMessage: {
            message.text = address + ' : ' + msg;
        }
    }
    OSCSender {
        id: osc
        ip: '127.0.0.1'
        port: 3333
    }
    Timer {
        property int cnt: 0
        interval: 1000/60
        running: true
        repeat: true
        onTriggered: {
            osc.send('/Hoge/cnt', ++cnt);
        }
    }
}