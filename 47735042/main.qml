import QtQuick 2.8
import QtCharts 2.2
import QtQuick.Window 2.2

Window{
    visible: true
    width: 640
    height: 480

    Connections {
        target: dataFromCpp
        onWValueChanged: {
            if(lineSeries1.count > 5)
                lineSeries1.remove(0);
            lineSeries1.append(dataFromCpp.wValue.x, dataFromCpp.wValue.y)
            axisX.min = lineSeries1.at(0).x
            axisX.max = lineSeries1.at(lineSeries1.count-1).x
        }
    }

    ChartView {
        id: chartView
        width: parent.width
        height: parent.height
        anchors.fill: parent
        animationOptions: ChartView.NoAnimation
        antialiasing: true
        backgroundColor: "#1f1f1f"

        ValueAxis {
            id: axisY1
            min: 0
            max: 100
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelFormat: "%.0f"
        }

        ValueAxis {
            id: axisX
            min: 0
            max: 50
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelFormat: "%.0f"
            tickCount: 5
        }

        LineSeries {
            id: lineSeries1
            name: "signal 1"
            color: "white"
            axisX: axisX
            axisY: axisY1
        }
    }
}
