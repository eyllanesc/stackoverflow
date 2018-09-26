import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 320
    height: 240
    title: qsTr("ComboBox with SqlTableModel")
    ComboBox {
        anchors.centerIn: parent
        model: cppmodel
        textRole: "name"
        Component.onCompleted: currentIndex = 4
        onCurrentIndexChanged: {
            var id = cppmodel.data(currentIndex, "id");
            var name = cppmodel.data(currentIndex, "name");
            console.log(qsTr("currentIndex: %1, id: %2, name: %3").arg(currentIndex).arg(id).arg(name))
        }
    }
}
