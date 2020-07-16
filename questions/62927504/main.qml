import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.1
import MyCalendar 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 400
    minimumWidth: 400
    minimumHeight: 300
    color: "#f4f4f4"

    title: "Calendar Example"

    SystemPalette {
        id: systemPalette
    }

    CalendarProvider {
        id: eventModel
        onLoaded: {
            // reload
            loader.sourceComponent = null
            loader.sourceComponent = page_component
        }
        Component.onCompleted: {
            eventModel.updateListEvents({
                calendarId: "primary",
                timeMin: new Date(),
                maxResults: 10,
                singleEvents: true,
                orderBy: "startTime",
            })
        }
    }

    Loader{
        id: loader
        anchors.fill: parent
        sourceComponent: page_component
    }

    Component{
        id: page_component
        Flow {
            id: row
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10
            layoutDirection: Qt.RightToLeft

            Calendar {
                id: calendar
                width: (parent.width > parent.height ? parent.width * 0.6 - parent.spacing : parent.width)
                height: (parent.height > parent.width ? parent.height * 0.6 - parent.spacing : parent.height)
                frameVisible: true
                weekNumbersVisible: true
                selectedDate: new Date()
                focus: true
                style: CalendarStyle {
                    dayDelegate: Item {
                        readonly property color sameMonthDateTextColor: "#444"
                        readonly property color selectedDateColor: Qt.platform.os === "osx" ? "#3778d0" : systemPalette.highlight
                        readonly property color selectedDateTextColor: "white"
                        readonly property color differentMonthDateTextColor: "#bbb"
                        readonly property color invalidDatecolor: "#dddddd"

                        Rectangle {
                            anchors.fill: parent
                            border.color: "transparent"
                            color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "transparent"
                            anchors.margins: styleData.selected ? -1 : 0
                        }

                        Image {
                            visible: eventModel.eventsForDate(styleData.date).length > 0
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: -1
                            width: 12
                            height: width
                            source: "images/eventindicator.png"
                        }

                        Label {
                            id: dayDelegateText
                            text: styleData.date.getDate()
                            anchors.centerIn: parent
                            color: {
                                var color = invalidDatecolor;
                                if (styleData.valid) {
                                    // Date is within the valid range.
                                    color = styleData.visibleMonth ? sameMonthDateTextColor : differentMonthDateTextColor;
                                    if (styleData.selected) {
                                        color = selectedDateTextColor;
                                    }
                                }
                                color;
                            }
                        }
                    }
                }
            }

            Component {
                id: eventListHeader

                Row {
                    id: eventDateRow
                    width: parent.width
                    height: eventDayLabel.height
                    spacing: 10

                    Label {
                        id: eventDayLabel
                        text: calendar.selectedDate.getDate()
                        font.pointSize: 35
                    }

                    Column {
                        height: eventDayLabel.height

                        Label {
                            readonly property var options: { weekday: "long" }
                            text: Qt.locale().standaloneDayName(calendar.selectedDate.getDay(), Locale.LongFormat)
                            font.pointSize: 18
                        }
                        Label {
                            text: Qt.locale().standaloneMonthName(calendar.selectedDate.getMonth())
                                  + calendar.selectedDate.toLocaleDateString(Qt.locale(), " yyyy")
                            font.pointSize: 12
                        }
                    }
                }
            }

            Rectangle {
                width: (parent.width > parent.height ? parent.width * 0.4 - parent.spacing : parent.width)
                height: (parent.height > parent.width ? parent.height * 0.4 - parent.spacing : parent.height)
                border.color: Qt.darker(color, 1.2)

                ListView {
                    id: eventsListView
                    spacing: 4
                    clip: true
                    header: eventListHeader
                    anchors.fill: parent
                    anchors.margins: 10
                    model: eventModel.eventsForDate(calendar.selectedDate)

                    delegate: Rectangle {
                        width: eventsListView.width
                        height: eventItemColumn.height
                        anchors.horizontalCenter: parent.horizontalCenter

                        Image {
                            anchors.top: parent.top
                            anchors.topMargin: 4
                            width: 12
                            height: width
                            source: "images/eventindicator.png"
                        }

                        Rectangle {
                            width: parent.width
                            height: 1
                            color: "#eee"
                        }

                        Column {
                            id: eventItemColumn
                            anchors.left: parent.left
                            anchors.leftMargin: 20
                            anchors.right: parent.right
                            height: timeLabel.height + nameLabel.height + 8

                            Label {
                                id: nameLabel
                                width: parent.width
                                wrapMode: Text.Wrap
                                text: modelData["summary"]
                            }
                            Label {
                                id: timeLabel
                                width: parent.width
                                wrapMode: Text.Wrap
                                text: modelData.start.toLocaleTimeString(calendar.locale, Locale.ShortFormat) + "-" + modelData.end.toLocaleTimeString(calendar.locale, Locale.ShortFormat)
                                color: "#aaa"
                            }
                        }
                    }
                }
            }
        }
    }
}
