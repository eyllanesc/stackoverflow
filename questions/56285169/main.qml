import QtQuick 2.12
import QtQuick.Window 2.12

import QtLocation 5.12
import QtPositioning 5.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Plugin {
        id: mapPlugin
        name: "osm"
    }
    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(14.70202102, 121.0957246)
        zoomLevel: 15
        MapQuickItem{
            id: marker
            anchorPoint.x: marker.width / 4
            anchorPoint.y: marker.height
            coordinate: manager.position
            sourceItem:  Image { source: "qrc:/marker.png"
                Text { text: "Location" ; font.pointSize: 8; font.bold: true }
            }
        }
    }
}
