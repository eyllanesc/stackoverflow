import QtQuick 2.12
import QtLocation 5.12
import QtPositioning 5.12

Item {
    width: 1200
    height: 1000
    visible: true

    Plugin {
        id: osmPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(45.782074, 4.871263)
        zoomLevel: 5

        MapItemView {
            model : myModel
            delegate: MapQuickItem {
                coordinate: model.position
                sourceItem: Image {
                    id: image_1
                    source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
                }
                anchorPoint.x: image_1.width / 2
                anchorPoint.y: image_1.height / 2
            }
        }
    }
}
