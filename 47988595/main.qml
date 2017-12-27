import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button
        x: 270
        y: 47
        text: qsTr("Button")
    }

    TextField {
        id: textField
        x: 220
        y: 169
        text: qsTr("Text Field")
    }

    onActiveFocusControlChanged:  {
        var className = helper.getClassName(activeFocusControl)
        switch(className){
        case "QQuickTextField":
            console.log("I am QQuickTextField")
            break
        case "QQuickButton":
            console.log("I am QQuickButton")
            break
        default:
            console.log("empty")
        }
    }
}
