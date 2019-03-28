import QtQuick 2.0
import QtLocation 5.12

MapQuickItem{
    id: marker
    anchorPoint.x: marker.width / 4
    anchorPoint.y: marker.height
    sourceItem: Image{
        id: icon
        source: "marker.png"
        sourceSize.width: 40
        sourceSize.height: 40
    }
}
