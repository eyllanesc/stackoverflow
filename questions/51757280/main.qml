import QtQuick 2.9
import QtQuick.Window 2.2
import Wormhole 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    VizFactory{
        options:
            LayoutOptions{
            type: "row"
            childOptions: [
                FooOptions{},
                LayoutOptions{
                    type: "col"
                    childOptions: [
                        FooOptions {},
                        FooOptions {}
                    ]
                }
            ]
        }
    }
}
