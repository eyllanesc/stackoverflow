import QtQuick 2.0
import QtQuick.Window 2.3

Item {
    Timer{
        id: timer
        interval: 1000; running: true; repeat:true
        onTriggered:{
            console.log("ex")
            test.testFunc();
        }
    }
}
