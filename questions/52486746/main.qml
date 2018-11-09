import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item
{
    id: root
    width: 512
    height: 512
    visible: true
    property point center: mainwindow.center
    property string title: mainwindow.title

    Plugin
    {
        id: mapPlugin
        name: "osm"
    }

    Map
    {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(root.center.x, root.center.y)
        zoomLevel: 15

        ListModel
        {
            id: locationModel
            ListElement {lat: 0; lon: 0; color: "blue"}
            ListElement {lat: 5; lon: 12.5; color: "green"}
            ListElement {lat: 10; lon: 25; color: "red"}
        }

        MapItemView
        {
            model: locationModel
            delegate: MapQuickItem
            {
                coordinate: QtPositioning.coordinate(root.center.x, root.center.y)
                anchorPoint: Qt.point(10 , 10)
                sourceItem: Column
                {
                    Image {source: "marker.png"}
                    Text {text: root.title}
                }
            }
        }
    }
}
