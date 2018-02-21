import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0

import "."

Tab{
    title:"FAVORITES"
    id:favtab

    ListView {
        id:favorites
        width: parent.width
        height: parent.height
        focus: true
        interactive: true
        clip: true
        model: Shared.favModel
        delegate: ListItem {
            text: model.title
            onClicked: pageStack.push(model.source)
        }
    }
}
