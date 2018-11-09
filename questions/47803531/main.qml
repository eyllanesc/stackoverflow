import QtQuick 2.9
import QtQuick.Window 2.2
import EngineModule 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        x:200
        y:200
        id: name
        text:s.limits.min
    }

    SplitBarGauge {
        id: s
        height: 200
        width: 500
        limits: Limits {
            id: qtyLimits
            min: 4
        }
    }
    Timer{
        interval: 1000; running: true; repeat: true
        onTriggered: qtyLimits.min += 2;
    }
}
