import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0
import Qt.labs.settings 1.0
Page{
    title:qsTr("Page1")
    appBar.maxActionCount: 2
    id:sampleapp
    property string datastore: ""
    property int countt2: 0
    Settings{
        id:mysetting4
        property alias datastore: sampleapp.datastore
        property alias mycount: sampleapp.countt2
    }
    FavModel{
        id:dataModel
    }

    ListView{
        anchors.fill: parent
        delegate: ItemDelegate {
            width: parent.width
            text: model.title
        }
        model: dataModel
    }

    Component.onCompleted: {
        console.log("onCompleted works right now.")
        if(datastore){
            dataModel.clear()
            var datamodel = JSON.parse(datastore)
            for (var i=0; i<datamodel.length; ++i) dataModel.append(datamodel[i])
        }
    }
    Component.onDestruction: {
        console.log("onDestruction works right now.")
        var datamodel=[]
        for (var i=0; i<dataModel.count; ++i) datamodel.push(dataModel.get(i))
        datastore = JSON.stringify(datamodel)
        console.log("datastore: "+datastore)
    }

    actions: [
        Action {
            id:favourite2
            onTriggered:{
                countt2++
                console.log("Count/2: "+ countt2%2)
                if(dataModel.count==0){
                    console.log("List must be added")
                    dataModel.append({ "title": "Application Tools", "source": "qrc:/SamplePage.qml" })
                }
                else{
                    console.log("List must be removed.")
                    return dataModel.remove(dataModel.index)
                }
            }
            icon.name: "toggle/star"
            toolTip: qsTr("Add/Remove")
        }
    ]
}
