import QtQuick 2.0
import QtLocation 5.6

MapQuickItem {
    sourceItem: Loader{
        sourceComponent:
            if(type == 0)//some condition
                return idRect
            else if(type == 1) //another condition
                return idCircle

    }
    Component{
        id: idRect
        Rectangle{
            width: 20
            height: 20
            color: "blue"
        }
    }
    Component{
        id: idCircle
        Rectangle{
            color: "red"
            width: 20
            height: 20
            radius: 50
        }
    }
}
