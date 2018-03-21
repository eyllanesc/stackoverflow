import QtQuick 2.9
import QtQuick.Controls 1.4

Button {
    id: test
    text: "test"
    objectName : "Button"
    onClicked: {
    	console.log("Component")
        configurator.sum(1, 2)
        configurator.info("TestOutput")
    }
}