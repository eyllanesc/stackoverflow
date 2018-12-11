import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "tabBars"
    ListModel{
        id: tabmodel
    }
    function assertCDataTabs(){
        var tabs = [QT_TR_NOOP("Configuration"),
                    QT_TR_NOOP("Devices"),
                    QT_TR_NOOP("Sounders"),
                    QT_TR_NOOP("Zones")]
        for (var i in tabs)
            tabmodel.append({"text": tabs[i] })
    }
    header: TabBar{
        id: tabBar
        opacity:0.8
        Repeater{
            model: tabmodel
            TabButton{
                text: qsTr(tabmodel.get(index).text)
                font.pixelSize: 14
            }
        }
    }
    Column {
        width: parent.width * 0.95
        spacing: 15
        padding: 15
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater{
                model: trans.languages
                Button{
                    id: btn
                    property string code: modelData
                    text: trans.languageByCode(code)
                    onClicked: trans.selectLanguage(btn.code)
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    highlighted: code == trans.currentLanguage
                }
            }
        }
    }
    Component.onCompleted: assertCDataTabs()
}
