import QtQuick 2.9
import QtQuick.Window 2.2

import QtPositioning 5.6
import QtLocation 5.6

Window {
    visible: true
    width: 640
    height: 480

    Plugin {
        id: osmMapPlugin
        name: "osm"
    }
    Map {
        anchors.fill: parent
        plugin: osmMapPlugin
        center: QtPositioning.coordinate(56.006355, 92.860984)
        zoomLevel: 10

        MapCircle {
            center: circleController.center
            radius: circleController.radius
            color: 'green'
            border.width: 3
        }
    }
}
