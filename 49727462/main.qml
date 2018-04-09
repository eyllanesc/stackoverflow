import QtQuick 2.9
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    visibility: "FullScreen"

    title: qsTr("Hello World")

    Map {
        id: mapOfWorld
        anchors.centerIn: parent;
        anchors.fill: parent
        zoomLevel: 10
        plugin: Plugin {name: "osm"}
        center: QtPositioning.coordinate(41.97732, -87.90801)//KORD

        MapItemView {
            model: assetmodel
            delegate: AssetTrail{
                path: history
                line.color: color
            }
        }

        MapItemView {
            model: assetmodel
            delegate: MapMarker{
                coordinate: asset
            }
        }
    }

    // testing
    property var last_pos1: mapOfWorld.center
    property var last_pos2: mapOfWorld.center

    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: {
            last_pos1 = QtPositioning.coordinate(last_pos1.latitude + 0.1*(Math.random()-0.5),
                                                last_pos1.longitude + 0.1*(Math.random()-0.5))
            assetmodel.addAsset(last_pos1, "testing_name1")
            last_pos2 = QtPositioning.coordinate(last_pos2.latitude + 0.1*(Math.random()-0.5),
                                                last_pos2.longitude + 0.1*(Math.random()-0.5))
            assetmodel.addAsset(last_pos2, "testing_name2")
        }
    }

}
