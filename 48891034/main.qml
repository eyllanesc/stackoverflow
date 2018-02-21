import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Fluid.Controls 1.0
import QtQuick.Window 2.3
ApplicationWindow{
    id:main
    width: 640
    height: 480
    visible:true
    title: "Example App"
    initialPage:TabbedPage {
        title: main.title
        Tab{
            title:"APPS"
            ListView {
                id:malist
                width: parent.width
                height: parent.height
                focus: true
                interactive: true
                clip: true
                model:ListModel {
                    id:appModel
                    ListElement { title: qsTr("Page1"); source: "qrc:/SamplePage.qml" }
                }
                delegate: ListItem {
                    text: model.title
                    onClicked: pageStack.push(model.source)
                }
            }
        }
        Favourites{}
    }
}
