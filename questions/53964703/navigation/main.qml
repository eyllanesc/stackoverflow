import QtQuick 2.9
import QtQuick.Controls 2.2
import QtLocation 5.11
import QtPositioning 5.11
import QtQuick.LocalStorage 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import SqlQueryModel 1.0

ApplicationWindow {
    id: app_window
    visible: true
    width: 900 //Breite des Fensters
    height: 800 //Höhe des Fensters
    title: qsTr("Navigation") //Titel

    SqlQueryModel{
        id: querymodel
        query: "select * from coordinates"
    }

    onActiveChanged:
    {
        console.log("MapQuickItem:", marker_id.coordinate);
    }


    Plugin {
        id: mapPlugin_
        name: "osm" //plugin, das die OpenStreetMaps included
    }

    Loader { //QtQuick Komponent, der verantwortlich ist andere kommpoente aus einem weiteren datei.qml zu laden
        id: loadRoutingMenu
        source: "menu/routingMenu.qml"
        active: true
    }

    PositionSource {
        id: src //Name des PositionSource's, die danach für erkennung benutzt wird
        updateInterval: 1000 //wie oft sollte es unsere Lokalisation updaten
        active: true //wir schalten die Lokalisierung an
        //nmeaSource: '/dev/serial/by-id/usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0'

        onPositionChanged: { //wenn wir das signal bekommen
            var coord = position.coordinate;
            console.log("error value: " + src.sourceError) //zeigt uns evetuelle Fehler, die aufgetreten sind
            console.log("Coordinate:", coord.longitude, coord.latitude); //sollte unsere Länge und Breite im consol schreiben
            // uncomment next line
            //map_id.center = coord; // bewegt uns, bzw unseres zoom zu unsere Lokalisation
            marker_id.coordinate = coord;
        }
    } //PositionSource

    Rectangle { //hier als eine Rahme für das map
        id: mapRectangleID
        width: app_window.width //Übernahme des breite von ApplicationWindow
        height: app_window.height - 20 //Höhe des ApplicationWindow - 20 pixel, die für Button reserviert sind
        y: 20 //Verschiebung an y-achse um 20 Pixel nach unten
        Map {
            id: map_id
            anchors.fill: parent
            plugin: mapPlugin_
            center: QtPositioning.coordinate(51.1913436, 12.1632954) //Koordinaten Angabe für Anfangsort (Am kleinen Feld 3, 04205 Leipzig, Germany)
            zoomLevel: 30
            MapItemView{
                model: querymodel
                delegate:  MapCircle {
                    center: QtPositioning.coordinate(latitude, longitude)
                    radius: 1.0
                    color: 'blue'
                    border.width: 1
                }
            }
            MapQuickItem {
                id: marker_id
                coordinate: QtPositioning.coordinate(51.315804, 12.263470299999994)
                sourceItem: Image {
                    id: endPointImage
                    source: "assets/marker.png"
                    width: 30.125
                    height: 26.125
                } //size and position of maker
                anchorPoint.x: endPointImage.width / 2
                anchorPoint.y: endPointImage.height
            } //marker

            MapCircle {
                id: oldWayMapCircel
                radius: 50.0
                color: 'green'
                border.width: 3
            } //MapCircel


        } //Map
    } //Rectangle

    /*Address Komponente*/
    Address {
        id: fromAddress
        city: ""
        country: ""
        street: ""
        postalCode: ""
    } //fromAddress

    Address {
        id: toAddress
        country: ""
        city: ""
        street: ""
        postalCode: ""
    } //toAddress

    /* BUTTON SECTION */
    Button {
        id: btn_close
        width: 100
        height: 20
        text: "Close"

        onClicked: {
            Qt.quit();
        }
    }

    Button {
        id: btn_routing
        width: 100
        height: 20
        x:100
        text: "Routing"

        onClicked: {
            loadRoutingMenu.item.open(); //öffnet das Menu aus
        }
    }

    Button {
        id: btn_loadData
        width: 100
        height: 20
        x:200
        text: "Load data"

        onClicked: {
        }
    }

    Button {
        id: btn_getCoordinates
        width: 400
        height: 20
        x:300
        text: "Get coordinates from file"
        visible: true;

        onClicked: {
            menu_getCoordinates.open();
        }
    }
    Button {
        id: btn_drawWay
        width: parent.width - x
        height: 20
        x:700
        text: "Draw way"
        visible: true;

        onClicked: {
            menu_drawWay.open();
        } //onClicked bei MenuItem
    } //Button
    /********************************************MENU********************************************/
    Menu {
        id: menu_getCoordinates
        y:btn_getCoordinates.y + 20
        x:btn_getCoordinates.x
        width: btn_getCoordinates.width

        MenuItem {
            text: "Get coordinates from file"

            onTriggered: {
                fileDialog.visible = true; //wir schalten das fileDialog an
                console.log("Get coordinates of file")
            }
        }
        MenuSeparator {} //Zeichnt die Linie zwischen 2 MenuItems
        MenuItem {
            text: "Get coordinates of addresse"
            onTriggered: {
                console.log("Get coordinates of addresse")
            } //onClicked bei MenuItem

        }
    } //Menu

    Menu {
        id: menu_drawWay
        y:btn_drawWay.y + 20
        x:btn_drawWay.x

        MenuItem {
            text: "Draw old way"

            onTriggered: {
                console.log("Draw old way")
            }
        }
        MenuSeparator {} //Zeichnt die Linie zwischen 2 MenuItems
        MenuItem {
            text: "Routing beetwen 2 points"
            onTriggered: {
                console.log("Routing beetwen 2 points")
            } //onClicked bei MenuItem

        }
    } //Menu

    /**************************************** FileDialog SECTION********************************/
    FileDialog {
        id: fileDialog
        title: "Chooose a file"
        folder: shortcuts.home

        onAccepted: { //wenn ein Datei ausgewählt wurde
            console.log("You chose: " + fileDialog.fileUrls)
        }

        onRejected: { //Aktion abgebrochen
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }
} //ApplicationWindow
