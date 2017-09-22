import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column{

        Button{
            id:btn
            onClicked: {
                for(var i=0; i<myModel.rowCount(); i++){
                    console.log(myModel.data(myModel.index(i, 0)));
                }
                myModel.removeRows(0, 1);
            }
        }
        ListView{
            anchors.top: btn.bottom
            height: 100
            model: myModel
            delegate: Text {
                text: display
            }
        }
    }
}
