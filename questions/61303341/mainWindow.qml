import QtQuick 2.14
import QtQuick.Controls 2.14
import QtLocation 5.14

import MarkerModel 1.0

ApplicationWindow {
    id: appWindow
    width: 1512
    height: 1512
    visible: true
    x:100
    y:100


    MarkerModel{
        id: markerModel
    }


    Plugin {
          id: mapPlugin
          name: "osm"
      }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin

        MapItemView {
            model: markerModel
            delegate: routeMarkers
        }

        MapPolyline {
            line.width: 5
            path: markerModel.path
        }

        Component {
            id: routeMarkers
            MapCircle {
                radius: 10
                center: positionRole
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var coord = parent.toCoordinate(Qt.point(mouse.x,mouse.y))
                markerModel.addMarker(coord)
            }
        }

    }

}
