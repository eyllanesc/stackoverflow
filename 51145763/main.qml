import QtQuick 2.9
import QtQuick.Window 2.2

import com.eyllanesc.org 1.0

Window {
    id: win
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property LineItem currentItem: null

    Rectangle{
        id: canvas
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent

            onPressed: {
                currentItem = create_lineitem(canvas, "green")
                currentItem.startPos = Qt.point(mouseX,mouseY)
                currentItem.endPos = Qt.point(mouseX,mouseY)
            }
            onReleased:  currentItem.endPos = Qt.point(mouseX,mouseY)
            onPositionChanged: currentItem.endPos = Qt.point(mouseX,mouseY)
        }
    }

    function create_lineitem(parentItem, color) {
        var item = Qt.createQmlObject('import com.eyllanesc.org 1.0; LineItem{anchors.fill: parent}',
                                           parentItem);
        item.lineColor = color;
        return item;
    }

}
