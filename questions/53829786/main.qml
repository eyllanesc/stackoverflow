import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import Foo 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SyntaxHighlighterHelper{
        quickdocument: ta.textDocument
    }

    TextArea{
        id:ta
        anchors.fill: parent
        selectByMouse: true
        selectByKeyboard: true
        font.pointSize: 12
        textMargin: 16
        font.family:"courier new"
        persistentSelection: true
        textFormat: Text.StyledText
        tabStopDistance: 4*fontMetrics.advanceWidth(" ")
        FontMetrics {
            id: fontMetrics
            font.family: ta.font
        }
    }
}
