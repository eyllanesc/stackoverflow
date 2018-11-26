import QtQuick 2.9
import QtQuick.Window 2.2
import Customs 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextItem{
        text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum volutpat libero elit, eu egestas lacus lacinia nec. Curabitur tempus lectus est, eget blandit arcu lacinia non. Curabitur vestibulum dictum diam ut hendrerit. Sed vitae ultricies libero. Morbi non libero risus. Aenean vel volutpat ipsum, scelerisque lacinia dui. Donec molestie vitae dolor vitae porttitor. Phasellus et facilisis elit. Sed metus lacus, commodo non interdum eu, viverra eu justo. Praesent a blandit nisi, ac porta magna. Aenean a lectus vel tortor ullamcorper ornare id non quam. Suspendisse potenti. Nunc hendrerit, eros nec vestibulum egestas, dolor orci malesuada est, sit amet tristique ipsum sem in mauris. Nullam lorem lacus, laoreet non venenatis sit amet, consequat dictum ligula. Quisque bibendum tellus egestas ex ullamcorper dapibus."
        anchors.fill: parent
    }
}
