pragma Singleton
import QtQuick 2.8

QtObject {
    //Text Properties
    readonly property int fontSize: 10
    readonly property color primaryTextColor: "#D0D0D0"
    readonly property color disabledTextColor: "#909090"

    //F
    readonly property color focusedIconColor: "#D0D0D0"
    readonly property color diabledIconColor: "red"

    readonly property color primaryBackgroundColor:  "#2A2A2A"
    readonly property color secondaryBackgroundColor: "#363636"

    //All Button Properties
    readonly property color disabledButtonColor: "#777777"

    //Primary Button Properties
    readonly property real primaryButtonBorderWidth: 2
    readonly property real primaryButtonBorderRadius: 5
    readonly property color primaryButtonBorderColor: "#D0D0D0"

    readonly property color primaryButtonColor: "#007acc"
    readonly property color primaryButtonHoverColor: "#018deb"
    readonly property color primaryButtonPressedColor: "#0165a8"

    //Toolbar Button Properties
}
