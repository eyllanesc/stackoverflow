import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ChartView {
        anchors.fill: parent
        id: chart

        DateTimeAxis {
            id: axisX
            format: "HH:mm:ss"
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 10000
        }

        LineSeries{
            id: line
            axisX: axisX
            axisY: axisY
        }

        VXYModelMapper {
            id: modelMapper
            model: lineModel // QStandardModel in C++
            series: line
            firstRow: 1
            xColumn: 1
            yColumn: 2
        }
    }
}
