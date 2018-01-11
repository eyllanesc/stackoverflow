//================================
// main.qml
//================================
import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    id: qmlMap

    Plugin {
        id: osmPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 10
        objectName: "mainMap"

        MapQuickItem {
            id: marker
            objectName: "mapItem"
            coordinate {latitude: 59.91
                longitude: 10.75}
            anchorPoint.x: image.width * 0.5
            anchorPoint.y: image.height

            sourceItem: Image {
                id: image
                height: 35
                width: 35
                source: "mm_20_gray.png"
            }
            function recenter(lat,lng) {
                map.clearMapItems();
                marker.coordinate.latitude = lat;
                marker.coordinate.longitude = lng;
                map.addMapItem(marker);
                map.center.latitude = lat;
                map.center.longitude = lng;
                map.update();
            }
        }
    }
}
