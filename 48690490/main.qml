import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.2

import com.eyllanesc.models 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    visibility: Window.FullScreen

    ChartView {
        anchors.fill: parent
        antialiasing: true

        StackedBarSeries {
            VBarModelMapper {
                model: SqlTrafficModel {
                    id: trafficModel
                    queryStr: "select * from traffic"
                    onModelReset: bar_axis.categories = getColumn(0)
                    Component.onCompleted: bar_axis.categories = getColumn(0)
                }
                firstBarSetColumn: 1
                lastBarSetColumn: 2
                firstRow: 0
            }
            axisX: BarCategoryAxis {
                id: bar_axis
            }
        }
    }
}
