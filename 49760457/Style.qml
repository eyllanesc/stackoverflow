pragma Singleton
import QtQuick 2.0
QtObject
{
    property color green: "#558B2F"
    property color red: "#DD2C00"
    property color black: "black"

    property int dialogPopupDuaration: 100
    property int dialogTimeoutValue : 1500
    property int splashTimeout: 5000
    property int rotation: 180

    //Dialog Types
    property int dialogInfo: 0
    property int dialogProcessing: 1
    property int dialogSuccess: 2
    property int dialogFailure: 3

    //Settings
    property int manualOffset: 0
    property int calibrationTimeout: 1
    property bool isUnitMM: true
    property bool isBrightnessHigh: false
    property bool isDMPInit: false
    property int batteryThreshold: 33
    property int batterWarningOffset: 3

    //Uncomment the below lines and run
    //the app will no longer print the qW
    //until i console.log() in main.qml

    //            readonly property int boneS: 1
    //            readonly property int boneN: 0
    //            property int boneType: boneS

    //            property int boneTN: boneN
    //            property int boneTP: boneN

    //Default quaternion values for the 3D obj
    //to face towards the screen
    property real qX: 0.0
    property real qY: -1.0
    property real qZ: 0.0
    property real qW: -0.5

    property real tolerance: 0.02

    //IMU requires 30s from boot to settle down
    //so if user tries to calibrate it before that
    //use this bool to show warning
    property bool isThirtySecElapsed: false

    readonly property string appVersion: "v1.0.2"
}
