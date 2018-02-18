import QtQuick 2.0
import QtQuick.Layouts 1.3
import './js/GameUtils.js' as GameUtils

GridLayout {
    id: area
    anchors.fill: parent
    anchors.margins: 25
    columns: (width < height) ? 4 : Math.round(repeater.model / 4)
    rowSpacing: 5
    columnSpacing: 5

    property int imageCount: 10
    property int repeatCount: (repeater.model > imageCount)
                              ? repeater.model / imageCount : 1
    property variant imageIndexes: GameUtils.generateCardIndexes(
                                       imageCount, repeatCount)

    property int lastIndex : -1


    Repeater {
        id: repeater
        model: 40
        Card {
            id: card
            backImageSource: 'qrc:/images/img_' + area.imageIndexes[index] + '.jpg'
            onFinished: verify(index)
        }
    }

    function verify(index){
        if(lastIndex == -1){
            lastIndex = index
            return
        }
        area.enabled = false
        var lastItem = repeater.itemAt(lastIndex)
        var currentItem = repeater.itemAt(index)

        if(lastItem.backImageSource === currentItem.backImageSource){
            lastItem.state = "remove"
            currentItem.state = "remove"
        }
        else{
            lastItem.flipped = false
            currentItem.flipped = false
        }
        if(repeater.model === 0){
            console.log("Winning")
        }
        lastIndex = -1
        area.enabled = true
    }
}
