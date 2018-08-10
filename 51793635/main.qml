import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("ChartView Example")

    ChartView{
        title: "Line"
        anchors.fill: parent
        antialiasing: true

        ValueAxis{
            id: _axisX;
            min: uiData.xmax -uiData.xmin > 10 ? uiData.xmax -10 : uiData.xmin
            max: uiData.xmax
        }
        ValueAxis{
            id: _axisY;
            min: uiData.ymin -1
            max: uiData.ymax +1
        }
        LineSeries{
            id: _xySeries;
            axisX: _axisX;
            axisY: _axisY;
        }
    }
    Component.onCompleted: uiData.xy = _xySeries
}
