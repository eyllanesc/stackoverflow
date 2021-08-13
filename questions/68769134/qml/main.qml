import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: root

    property string qmlProperty: qsTr("QML Example String")

    width: 200
    height: 400
    visible: true

    Column {
        Text {
            text: qsTranslate("pythonModel", pythonModel.pythonProperty)
        }

        Text {
            text: root.qmlProperty
        }

    }

}
