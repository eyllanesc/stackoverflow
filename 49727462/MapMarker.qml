import QtQuick 2.0
import QtLocation 5.9

MapQuickItem
{
    property int spatialPointHeight: 60
    id: assetMapItem2
    property string name: ""
    property bool followMe: false
    property real transparency: 0.5
    anchorPoint.x: assetIcon2.width/2
    anchorPoint.y: assetIcon2.height/2
    visible: true
    sourceItem: Column
    {
        Image
        {
            id: assetIcon2
            sourceSize.width: spatialPointHeight
            sourceSize.height: spatialPointHeight
            width: spatialPointHeight
            height: spatialPointHeight
            // Fade out all icons except for the last one
            opacity: 1 - assetMapItem2.transparency
            source: "qrc:/chopper.png"
            transform: Rotation
            {
                id: assetRotation2
                origin.x: spatialPointHeight/2
                origin.y: spatialPointHeight/2
                angle: 90
            }
        }
        Text
        {
            text: name
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            width: assetIcon2.width + 10
        }
    }
}
