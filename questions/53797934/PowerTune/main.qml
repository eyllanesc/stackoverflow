import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import com.powertune 2.0

ApplicationWindow  {
    visible: true
    width: 800
    height: 480
    minimumWidth: 800
    minimumHeight: 480
    title: qsTr("PowerTune 2.0")
    color: "grey"


    ListView {
        id: listviewMain
        width: 100; height: 800
        model: dataSourceModel
        delegate: mydelegate
        }

    Component {
        id: mydelegate
        Text { text: name + " " + value }
    }
    ColumnLayout{
        anchors.right: parent.right
        ComboBox {
            id: cbx_sources
            textRole: "name"
            width: 200;
            model: dataSourceModel
            onCurrentIndexChanged: text2.text = dataSourceModel.get(currentIndex).value
            Component.onCompleted: currentIndex = 1
        }
        Button {
            id: button
            text: qsTr("Add")
            highlighted: false
            checkable: false
            autoExclusive: false
            checked: false
        }
        Text {
            id: text1
            width: 100
            height: 31
            text: cbx_sources.currentIndex.toString()
            font.pixelSize: 12
        }
        Text {
            id: text2
            width: 100
            height: 31
            font.pixelSize: 12
        }
    }

}
