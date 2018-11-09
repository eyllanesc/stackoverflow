import QtQuick 2.0
import QtLocation 5.6

MapQuickItem {
    id: idPointsMarker
    sourceItem: Loader{sourceComponent: idRect}
    visible: map.isVisibleItems

    Component{
        id: idRect
        Rectangle{
            width: 20
            height: 20
            color: "blue"
        }
    }
}
