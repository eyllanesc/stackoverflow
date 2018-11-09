import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: SingletonClass.text



    Button {
        text: "Button"
        onClicked: SingletonClass.someMethodCalledFromQml()
    }
}
