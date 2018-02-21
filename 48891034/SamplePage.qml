import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0
import "."

Page{
    title:qsTr("Page1")
    appBar.maxActionCount: 2
    id:sampleapp

    actions: [
        Action {
            id:favourite2
            onTriggered:{
                Shared.favModel.append({ "title": "Application Tools", "source": "qrc:/SamplePage.qml" })
            }
            icon.name: "toggle/star"
            toolTip: qsTr("Add/Remove")
        }
    ]
}
