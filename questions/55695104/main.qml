import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int decimalplaces: 4

    Component {
        id: textcomponent
        Text {
            text: value.toFixed(decimalplaces)
        }
    }
    Repeater{
        model: dataSourceModel
        Loader{
            property real value: model.value
            sourceComponent: index == 88 ? textcomponent: null
        }
    }
}
