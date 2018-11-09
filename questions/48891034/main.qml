import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Fluid.Controls 1.0
import QtQuick.Window 2.3
import Qt.labs.settings 1.0
import "."

ApplicationWindow{
    id:main
    width: 640
    height: 480
    visible:true
    title: "Example App"

    property string datastore: ""
    Settings{
        property alias datastore: main.datastore
    }

    Component.onCompleted: {
        console.log("onCompleted works right now.")
        if(datastore){
            Shared.favModel.clear()
            var datamodel = JSON.parse(datastore)
            for (var i=0; i<datamodel.length; ++i) Shared.favModel.append(datamodel[i])
        }
    }

    Component.onDestruction: {
        console.log("onDestruction works right now.")
        var datamodel=[]
        for (var i=0; i<Shared.favModel.count; ++i) datamodel.push(Shared.favModel.get(i))
        datastore = JSON.stringify(datamodel)
        console.log("datastore: "+datastore)
    }

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
        Favourites{

        }
    }
}
