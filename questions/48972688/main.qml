import QtQuick 2.9
import QtQuick.Window 2.2
import "utils.js" as Util

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListModel {
        id: fruitModel
        ListElement {
            name: "Apple"
            cost: 2.45
        }
        ListElement {
            name: "Banana"
            cost: 1.95
        }
        ListElement {
            name: "Orange"
            cost: 3.25
        }
    }

    Column {
        Repeater {
            model: Util.shuffle(fruitModel)
            Row {
                spacing: 10
                Text { text: name }
                Text { text: '$' + cost }
            }
        }
    }
}
