import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property string path: ""
    onPathChanged: image.source = path == "" ? "": "image://provider/"+ path
    ColumnLayout {
        anchors.fill: parent
        Image {
            id: image
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 0.8
            fillMode: Image.PreserveAspectFit
        }
        Pane {
            id: pane
            Layout.fillWidth: true
            RowLayout {
                width: parent.width
                Button {
                    id: selectBtn
                    text: qsTr("Select")
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: fileDialog.open();
                }
                Button {
                    id: processBtn
                    text: qsTr("Process")
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if(path != "")  image.source = "image://provider/"+ path + "?edit=true"
                }
            }
        }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted:  path = fileDialog.fileUrl
    }
}
