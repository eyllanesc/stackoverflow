import QtQuick 2.14
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Window {
    visible: true
    width: 640
    height: 480
    Plugin {
        id: mapPlugin
        name: "osm"
    }
    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 10
        MapItemView{
            model: datamodel
            delegate: MapQuickItem{
                id: item
                // begin configuration
                property var position: model.position
                property var nextposition: model.nextposition
                onPositionChanged: restart();
                onNextpositionChanged: restart();
                function restart(){
                    anim.stop()
                    anim.from = position
                    anim.to = nextposition
                    anim.start()
                }
                CoordinateAnimation {
                    id: anim
                    target: item
                    duration: 60 * 1000
                    property: "coordinate"
                }
                // end of configuration
                anchorPoint.x: rect.width/2
                anchorPoint.y: rect.height/2
                sourceItem: Rectangle{
                    id: rect
                    color: "green"
                    width: 10
                    height: 10
                }
            }
        }
    }
}
