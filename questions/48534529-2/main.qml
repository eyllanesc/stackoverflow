import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import com.eyllanesc.filemanager 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    FileManager{
        id: manager
        folder: "/home/eyllanesc"
        nameFilters: ["*.mp4"]
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {

            ListView {
                id: lv
                width: 200; height: 400

                Component {
                    id: fileDelegate
                    Text { text: fileName
                        MouseArea{
                            anchors.fill: parent
                            onClicked: playMusic(index)
                        }
                    }
                }

                model: manager.files
                delegate: fileDelegate
            }

            Button {
                id: button
                anchors.top: lv.bottom
                width: parent.width
                text: "Play"
                background: Rectangle {
                    implicitHeight: 40
                    border.color: "#26282a"
                    border.width: 2
                    radius: 4
                }
                onClicked: playMusic(0)
            }
        }

        Page {
            MediaPlayer {
                id: player
                onStopped: {
                    if(status===MediaPlayer.EndOfMedia){
                        playMusic((lv.currentIndex+1) % lv.count)
                    }
                }
            }

            VideoOutput {
                id: video
                anchors.fill: parent
                source: player
            }
        }
    }

    function playMusic(index){
        player.stop()
        player.source = manager.files[index].url
        player.play()
        swipeView.setCurrentIndex(1)
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }
}
