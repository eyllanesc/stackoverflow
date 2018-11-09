import QtQuick 2.10
import QtQuick.Controls 2.3


Item {
    id: root
    property var value

    width: label.width
    height: label.height

    Component.onCompleted: {
        console.log(root.value)
    }

    Label {
        id: label
        text: root.value.currency.name
    }
}
