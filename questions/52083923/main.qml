import QtQuick 2.11
import QtQuick.Window 2.11

import test 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyItem {
        value: {
            var money = Factory.getMoney()
            console.log(money)
            return money
        }
        anchors.centerIn: parent
    }
}
