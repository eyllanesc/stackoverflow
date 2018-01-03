import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

import Config 1.0

Window {
    width: 800
    height: 480
    visible: true

    ColumnLayout{

        Text {
            id: someText
            text: Config.someOtherValue
        }
        Text {
            id: anotherText
            text: MainCpp.someValue
        }

        Slider {
            value: 0.5
            maximumValue: 100
            onValueChanged: MainCpp.update(value)
        }
    }
}
