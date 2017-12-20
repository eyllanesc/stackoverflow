import QtQuick 2.6
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6

Window {
    width: 700
    height: 500
    visible: true
    title: qsTr("Test implantation coordonnées")
    id: win

    property variant topLeftEurope: QtPositioning.coordinate(60.5, 0.0)
    property variant bottomRightEurope: QtPositioning.coordinate(51.0, 14.0)
    property variant viewOfEurope:
        QtPositioning.rectangle(topLeftEurope, bottomRightEurope)

    Map {
        id: mapOfEurope
        anchors.centerIn: parent;
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
        }
        MapItemView {
            model: navaidsModel
            delegate:  Marker{
                coordinate:  position
            }
        }
        visibleRegion: viewOfEurope
    }

}
