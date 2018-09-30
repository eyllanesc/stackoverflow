import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SwipeView Test")

    SwipeView {
        id: view
        anchors.fill: parent
        currentIndex: 4
        Repeater {
            model: 10
            Loader {
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                sourceComponent: Item{
                    Text {
                        text: "Page: "+index
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
    Connections{
        target: manager
        onToRight: if(view.currentIndex + 1 != view.count) view.currentIndex += 1
        onToLeft: if(view.currentIndex != 0) view.currentIndex -= 1
    }

    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
