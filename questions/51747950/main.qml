import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick 2.11
import customApi 1.0

Window {
  id: root
  visible: true
  width: 500
  height: 500

  property var items: []

  Backend {
    id: backend
  }

  Row {
    Button {
      text: "button1"
      onClicked: {
        var item1 = Qt.createQmlObject("import customApi 1.0; CustomClass { name: \"first-name\" }", root);
        var item2 = Qt.createQmlObject("import customApi 1.0; CustomClass { name: \"second-name\" }", root);
        items.push(item1);
        items.push(item2);
      }
    }
    Button {
      text: "button2"
      onClicked: {
        backend.sendItems(items);
      }
    }
  }

}
