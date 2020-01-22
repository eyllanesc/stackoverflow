import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import GradesSqlDataModel 1.0

Window {
    id: window
    visible: true
    width: 640;
    height: 600;

    SqlQueryModel{
        id: sqlquerymodel
        query: "SELECT DISTINCT Semester FROM results"
    }
    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        interactive: true
        ListView{
            anchors.fill: parent
            model: sqlquerymodel
            delegate: ItemDelegate {
                width: parent.width
                text: model.Semester
            }
        }
    }
    Component.onCompleted: drawer.visible = true
}
