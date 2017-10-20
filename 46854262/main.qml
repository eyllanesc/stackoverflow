import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import com.examples.login 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Login")

    Login{
        id: login
        username: usernameField.text
        password: passwordField.text

    }

    Rectangle {
        anchors.fill: parent

        ColumnLayout {
            id: layoutLogin
            anchors.centerIn: parent
            anchors.margins: 3
            spacing: 3

            TextField {
                id: usernameField
                textColor: "black"
                Layout.fillWidth: true
                placeholderText: "Username"
            }

            TextField {
                id: passwordField
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: TextInput.Password
                textColor: "black"
            }

            Button {
                id: proccessButton
                text: "Login"
                Layout.fillWidth: true
                onClicked: login.test()

            }
        }
    }
}
