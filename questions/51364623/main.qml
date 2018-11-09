import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GridView {
        id: gv
        anchors.fill: parent
        model: manager.filterModel
        property int nextIndex : mod(currentIndex+1, count)
        property int previousIndex : mod(currentIndex-1, count)
        property var currentModelItem
        onCurrentModelItemChanged: model.currentItem = currentModelItem
        delegate:
            Rectangle {
            width: 100
            height: 100
            property var view: GridView.view
            property bool isCurrentItem: index === view.currentIndex
            property bool isPreviousItem : index === view.nextIndex
            property bool isNextItem : index === view.previousIndex
            color: isCurrentItem ? "red" : isNextItem ? "green"  : isPreviousItem ? "blue" : "yellow"
            rotation: isCurrentItem ? 180 : isNextItem ? 90  : isPreviousItem? -90  : 0
            onIsNextItemChanged: if(isNextItem) view.currentModelItem = modelData
            Text {
                text: modelData.getVar
                anchors.centerIn: parent
            }
        }
    }
    // https://stackoverflow.com/a/50770689/6622587
    function mod(n, p){
        var r = n % p;
        return r < 0 ? r + p : r;
    }
    Action {
        shortcut: "Right"
        onTriggered: gv.currentIndex = mod(gv.currentIndex + 1, gv.count)

    }
    Action {
        shortcut: "Left"
        onTriggered: gv.currentIndex = mod(gv.currentIndex - 1, gv.count)
    }
}
