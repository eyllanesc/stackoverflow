import QtQuick 2.0
import QtLocation 5.9

MapQuickItem
{
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    property real factor: 1

    sourceItem: Image
    {
        id: image
        width: 2*factor; height: 2*factor
        source: "qrc:/arrow.png"
    }

}
