import QtQuick 2.9
import QtQuick.Window 2.2

Window{
    width: 600
    height: 400
    visible: true
    Column{
        Repeater{
            model: theTop.middles();
            delegate: txtComp;
        }
    }
    Component{
        id: txtComp;
        Text{
            text: modelData.name
        }
    }
    Component.onCompleted: console.log(theTop.middle(0).name)
}
