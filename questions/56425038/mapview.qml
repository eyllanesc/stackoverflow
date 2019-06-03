import QtQuick 2.12
import QtLocation 5.12
import QtPositioning 5.12

Item {
    id: window
    Plugin{
        id: mapPlugin
        name:"osm"
    }
    Map{
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(15.4561,73.8021);
        zoomLevel: 14
        Marker{
            coordinate: marker_model.current
        }
        MapItemView{
            model: marker_model
            delegate: Marker{
                coordinate: model.position
            }
        }
    }
}
