import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.11
import org.docviewer.poppler 1.0 // <--- import
import QtQuick.Dialogs 1.3

Window {
    id: win
    visible: true
    width: 640
    height: 480
    title: qsTr("Poppler Example")

    function urlToPath(urlString) {
        var s
        if (urlString.startsWith("file:///")) {
            var k = urlString.charAt(9) === ':' ? 8 : 7
            s = urlString.substring(k)
        } else {
            s = urlString
        }
        return decodeURIComponent(s);
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: ["PDF files (*.pdf)", "All files (*)"]
        onAccepted: timer.running = true
        Component.onCompleted: visible = true
    }

    Timer {
        id: timer
        interval: 100; repeat: false
        onTriggered: {
            poppler.path = urlToPath(""+fileDialog.fileUrl)
            view.focus = true
        }
    }

    Poppler{
        id: poppler
    }

    ListView{
        id: view
        height: parent.height
        width: 100
        model: poppler.numPages
        delegate:  Image{
            id: image
            width: parent.width
            source: poppler.loaded? "image://poppler/page/" + (modelData+1): ""
            sourceSize.width: width
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    image.ListView.view.currentIndex = index
                    image.ListView.view.focus = true
                }
            }
        }
    }
    Flickable {
        height: parent.height
        anchors.left: view.right
        anchors.right: parent.right
        contentWidth: bigImage.width;
        contentHeight: bigImage.height
        boundsBehavior: Flickable.StopAtBounds
        Image{
            id: bigImage
            sourceSize.width: win.width - view.width
            source: (poppler.loaded && view.currentIndex >= 0)?  "image://poppler/page/"+(view.currentIndex+1): ""
        }
    }
}

