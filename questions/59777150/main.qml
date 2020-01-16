import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.4
import QtCharts 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ColumnLayout{
        anchors.fill: parent
        RowLayout{
            Button{
                text: "Create serie"
                Layout.fillWidth: true
                onClicked: helper.createSerie(chartview)
            }
            Button{
                text: "Clear series"
                Layout.fillWidth: true
                onClicked: helper.removeAllSeries(chartview);
            }
        }
        ChartView {
            id: chartview
            title: "Line"
            antialiasing: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            LineSeries {
                name: "LineSeries"
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 3; y: 2.1 }
                XYPoint { x: 8; y: 3.3 }
                XYPoint { x: 10; y: 2.1 }
                XYPoint { x: 11; y: 4.9 }
                XYPoint { x: 12; y: 3.0 }
                XYPoint { x: 13; y: 3.3 }
            }
            axes: [
                ValueAxis{
                    id: xAxis
                    min: 1.0
                    max: 15.0
                },
                ValueAxis{
                    id: yAxis
                    min: 0.0
                    max: 5.0
                }
            ]
        }
    }
}
