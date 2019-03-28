import QtQuick 2.9
import QtQuick.Window 2.2
import QtLocation 5.12
import QtPositioning 5.12

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Plugin {
        id: mapPlugin
        name: "osm"
    }
    function addMarker(latitude, longitude)
    {
        var Component = Qt.createComponent("qrc:///views/marker.qml")
        var item = Component.createObject(window, {
                                              coordinate: QtPositioning.coordinate(latitude, longitude)
                                          })
        map.addMapItem(item)
    }
    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.14, 14.15)
        zoomLevel: 14
        Component.onCompleted:addMarker(59.14, 14.15)
    }
}
