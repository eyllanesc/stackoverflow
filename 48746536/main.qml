import QtQuick 2.9
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6

Window {
    width: 700
    height: 500
    visible: true
    title: qsTr("Test MapPolyline for airport")
    id: win

    Map {
        id: mapOfWorld
        anchors.centerIn: parent;
        anchors.fill: parent
        zoomLevel: 12
        plugin: Plugin {name: "osm"}
        center: QtPositioning.coordinate(41.97732, -87.90801)//KORD
        MapItemView {
            model: airportsModel
            delegate:  Marker{
                path: runways
            }
        }
    }
}
