import QtQuick 2.9
import QtQuick.Controls 2.4

Menu {
    id: routingMenu
    width: maximumWidth
    height: 200
    y: 20
    //cascade: true

    //Singalen, bzw Eventen die für Komunikation zwischen verschiedne komponente benötigt werden
    //Wichtig, das Wort signal ist benötigt zu arbeiet zwischen verschedne .qml files
    signal sendCountryFromAddress ();
    signal sendCityFromAddress ();
    signal sendStreetFromAddress ();
    signal sendPostalCodeFromAddress ();

    signal sendCountryToAddress ();
    signal sendCityToAddress ();
    signal sendStreetToAddress ();
    signal sendPostalCodeToAddress ();






    Rectangle {
        Label {
            x: (app_window.width / 8)
            text: "FROM:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
        Label {
            y: routingMenu.height / 7
            text: "Country:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
        Label {
            y: routingMenu.height / 2.5
            text: "City:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
        Label {
            y: routingMenu.height / 1.6
            text: "Street:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
        Label {
            y: routingMenu.height / 1.2
            text: "Postal Code:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
    } //Rectangle

    Rectangle {
         x: app_window.width / 2
         Label {
             x: (app_window.width / 4)
             text: "TO:"
             font.pixelSize: 22
             font.italic: true
             color: "black"
         }
         Label {
             y: routingMenu.height / 7
             text: "Country:"
             font.pixelSize: 22
             font.italic: true
             color: "black"
         }
         Label {
             y: routingMenu.height / 2.5
             text: "City:"
             font.pixelSize: 22
             font.italic: true
             color: "black"
        }
        Label {
            y: routingMenu.height / 1.6
            text: "Street:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
        Label {
            y: routingMenu.height / 1.2
            text: "Postal Code:"
            font.pixelSize: 22
            font.italic: true
            color: "black"
        }
    } //Rectangle


    Rectangle{
        Rectangle{
                    id: if_FromAddressCountry
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 4
                    y: routingMenu.height / 7

                    TextInput {
                        id: txt_FromAddressCountry
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_FromAddressCity
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 4
                    y: routingMenu.height / 2.5

                    TextInput {
                        id: txt_FromAddressCity
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_FromAddressStreet
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 4
                    y: routingMenu.height / 1.6

                    TextInput {
                        id: txt_FromAddressStreet
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_FromAddressPostalCode
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 4
                    y: routingMenu.height / 1.2

                    TextInput {
                        id: txt_FromAddressPostalCode
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            } //Rectangle from Addresss

    Rectangle{
        Rectangle{
                    id: if_ToAddressCountry
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 1.3
                    y: routingMenu.height / 7

                    TextInput {
                        id: txt_ToAddressCountry
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_ToAddressCity
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 1.3
                    y: routingMenu.height / 2.5

                    TextInput {
                        id: txt_ToAddressCity
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_ToAddressStreet
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 1.3
                    y: routingMenu.height / 1.6

                    TextInput {
                        id: txt_ToAddressStreet
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            Rectangle{
                    id: if_ToAddressPostalCode
                    width: 100
                    height: 22
                    border.color: 'gray'
                    border.width: 2
                    x: app_window.width / 1.3
                    y: routingMenu.height / 1.2

                    TextInput {
                        id: txt_ToAddressPostalCode
                        anchors.fill: parent
                        anchors.margins: 4
                    }
                }
            } // Rectangle toAddresse

    Button {
        id: sendDataToItem
        width: 100
        height: 40
        x: app_window.width / 2.7
        text: "Send"

        onClicked: {
            /*
                        Schick daten zu from/to_Adresse. von inputfields
            */
            onSendCountryFromAddress: fromAddress.country = txt_FromAddressCountry.text;
            onSendCityFromAddress: fromAddress.city = txt_FromAddressCity.text;
            onSendStreetFromAddress: fromAddress.street = txt_FromAddressStreet.text;
            onSendPostalCodeFromAddress: fromAddress.postalCode = txt_FromAddressPostalCode.text;

            onSendCountryToAddress: toAddress.country = txt_ToAddressCountry.text;
            onSendCityToAddress: toAddress.city = txt_ToAddressCity.text;
            onSendStreetToAddress: toAddress.street = txt_ToAddressStreet.text;
            onSendPostalCodeToAddress: toAddress.postalCode = txt_ToAddressPostalCode.text;


            //endPointGeaocodeModel.query = toAddress;
            //endPointGeaocodeModel.update();
            //startPointGeaocodeModel.query = fromAddress;

            //routeQuery.addWaypoint(startPointGeaocodeModel.get(0).address);
            //routeQuery.addWaypoint(endPointGeaocodeModel.get(0).address);
        }
    } //sendDataToItem

} //Menu
