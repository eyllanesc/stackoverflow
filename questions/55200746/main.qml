import QtQuick 2.9
import QtQuick.Window 2.2
import SortFilterProxyModel 0.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Repeater{
        model: proxyModel
        Rectangle{
            x: model.rectrole.x
            y: model.rectrole.y
            width: model.rectrole.width
            height: model.rectrole.height
            color:  model.colorrole
            Text{
            	anchors.centerIn: parent
                text: model.namerole
            }
        }
    }

    SortFilterProxyModel {
        id: proxyModel
        sourceModel: sourcemodel
        filters: [
            ExpressionFilter{
                //  QRect([0-200], [0-300], *, *)
                expression: (model.rectrole.x >= 0 && model.rectrole.x <= 200) && (model.rectrole.y >= 0 && model.rectrole.y <= 300)
            }
        ]
    }

}
