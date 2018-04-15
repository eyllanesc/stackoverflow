import QtQuick 2.9
import QtQuick.Controls 2.3
import QtLocation 5.6
import QtPositioning 5.6

import Location 1.0

ApplicationWindow {
    visible: true
    id: win
    visibility: "FullScreen"

    ListView{
        id: lv
        model: locationModel
        height: parent.height
        clip: true
        width: 150
        delegate: Text{
            text: latitude.toFixed(2) + " : " + longitude.toFixed(2)
        }
    }

    Map {
        id: map
        height: parent.height
        width: parent.width-lv.width
        x: lv.width
        plugin: Plugin {
            id: mapPlugin
            name: "osm"
        }
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 10

        MapItemView {
            model: locationModel
            delegate: MapQuickItem {
                id: marker
                coordinate:  position
                anchorPoint.x: image.width/4
                anchorPoint.y: image.height
                sourceItem: Image {
                    id: image
                    source: "qrc:/mm_20_red.png"
                }
            }
        }
    }

    LocationModel{
        id: locationModel
        locations: [
            Location{
                latitude: 59.91
                longitude: 10.75
            },
            Location{
                latitude: 59.92
                longitude: 10.74
            }
        ]
        Component.onCompleted: {
            for(var i=0; i<10; i++){
                var latitude = map.center.latitude + 0.5*(Math.random()-0.5);
                var longitude = map.center.longitude + 0.5*(Math.random()-0.5);
                locationModel.appendLocation(latitude, longitude)
                // or
                var p = QtPositioning.coordinate(map.center.latitude + 0.5*(Math.random()-0.5),
                                                 map.center.longitude + 0.5*(Math.random()-0.5));
                locationModel.appendLocation(p)
            }
        }
    }

}

