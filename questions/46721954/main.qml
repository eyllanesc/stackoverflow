import QtQuick 2.0

Rectangle {
    width: 640
    height: 480

    function append(le) {
        scheduleModel.append(le)
    }
    ListModel {
        id: scheduleModel
    }

    ListView {
        anchors.fill: parent
        id: scheduleList
        model: scheduleModel
        delegate: scheduleItem

        section.property: "day"
        section.delegate: sectionDelegate
    }


    Component {
        id: scheduleItem
            Row {
                spacing: 15
                Text {
                    text: lesson
                }
                Text {
                    text: subject
                }
        }
    }

    Component {
        id: sectionDelegate
            Text {
                id: label
                text: section
            }
    }
}