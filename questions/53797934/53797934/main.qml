import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ListView{
        anchors.fill: parent
        model: dataSourceModelObject
        delegate: Text {
            width: 100
            height: 31
            text: JSON.stringify(all)
      }
    }
}
