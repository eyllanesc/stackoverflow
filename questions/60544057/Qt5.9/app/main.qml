import QtQuick 2.7
import QtQuick.Window 2.2
import QtLocation 5.6
import QtPositioning 5.5

Window {
    visible: true
    width: 640
    height: 480
    Plugin {
        id: mapPlugin
        name: "here"
        PluginParameter { name: "here.apiKey"; value: "{YOUR_API_KEY}" }
    }
    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14
    }
}
