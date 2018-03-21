import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4

ApplicationWindow {
    id: window
    visible: true
    width: 640
    color: "red"
    height: 480
    title: qsTr("Hello World")

    Button {
	    x: 100
	    y: 100
	    text: "ApplicationWindow"
	    onClicked: {
	    	console.log("ApplicationWindow")
	        configurator.sum(1, 2)
	        configurator.info("TestOutput")
	    }
    }
}