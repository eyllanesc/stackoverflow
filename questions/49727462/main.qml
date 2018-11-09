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
                path: historyData
                line.color: colorData
            }

        }

        MapItemView {
            model: assetmodel
            delegate: MapMarker{
                coordinate: assetData
                name: nameData
                //transformOrigin: Item.Center
                //rotation: angleData
                z:100
            }
        }


        MapItemView {
            model: nodemodel
            delegate: ArrowItem{
                coordinate: nodeData
                transformOrigin: Item.Center
                rotation: angleData
                z:100
                factor: mapOfWorld.zoomLevel
            }
        }
    }

}
