import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "#465775"

    TextField {
        id:textField
        anchors.top: parent.top ;anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: "Cerca Ricetta"
        width:parent.width*0.95
        font.pointSize: 12
        background: Rectangle {
                radius: 5
                width: parent.width
                implicitHeight: 30

        }

        onTextChanged: {
            //myModelFiltrato.setStringaFiltro(text)
            myModelFiltrato.string=text

        }

    }

    GridView {
     id:grid

     property int indiceCorretto: 0

     function updateModel(){
        // alternativa a mettere il datachanged nel metodo add ricetta
        model=0
        model=myModel

     }
     function increseCurrIndex(index){

         //calcolo il giusto current index per dare effetto di gridView con paginazione

         if(Math.floor(index/6)==0)
           grid.indiceCorretto= 0                           // altrimenti ho valore negativo
         else
           grid.indiceCorretto=(Math.floor(index/6))*6

     }

     onCountChanged: {

          // faccio queste operazioni per aggiornare il numero dei p.indicator quando filtro le tile
          myModel.numIndicatori=grid.count
         // per rendere attivo il click sull'ultima mattonella quando
         myModel.totTile=grid.count
     }

     width:parent.width
     height: parent.height* 0.70

     highlightMoveDuration: 500
     highlightFollowsCurrentItem: true

     anchors.horizontalCenter: parent.horizotalCenter
     anchors.verticalCenter: parent.verticalCenter

     cellWidth: parent.width/3
     cellHeight: parent.height/3
     model: myModelFiltrato
     delegate: tile

     onMovementEnded: {

        increseCurrIndex(currentIndex)
        currentIndex=indiceCorretto
     }
     flow: GridView.FlowTopToBottom
     flickDeceleration: 4500
     clip: true

     boundsBehavior: Flickable.StopAtBounds
     flickableDirection: Flickable.VerticalFlick
     snapMode: GridView.SnapToRow
     highlightRangeMode: GridView.StrictlyEnforceRange
     preferredHighlightBegin: 0
     preferredHighlightEnd:  0

    }

    Component {
       id: tile
       Item{
               width: grid.cellWidth
               height: grid.cellHeight
               Rectangle{

                   color: colore//"#EF6F6C"//Qt.rgba(Math.random(),Math.random(),Math.random(),0.90)
                   width:parent.height*0.90
                   height: parent.height*0.90
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   border.width: 2
                   border.color:"#FFFFFF"

                   Text {
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.left:parent.left
                       anchors.right: parent.right
                       horizontalAlignment: Text.AlignHCenter
                       text:nomeRicetta + " "+index.toString()
                       font.pointSize: 17
                       color: "#ffffff"
                       wrapMode: Text.WordWrap
                   }
                   MouseArea {

                       anchors.fill: parent
                       onClicked: {
                          if(index==myModel.totTile-1)
                             myModel.addRicetta("pane","green",2,true)
                       }
                       onPressAndHold: {
                          if (index != myModel.totTile-1){

                                    myModel.removeRows(index,1)
                          }

                       }
                   }
               }
       }
    }
    // page indicator circolare
    PageIndicator {
        id: control
        visible: false
        interactive: false
        count: myModel.numIndicatori
        currentIndex: Math.floor(grid.currentIndex/6)
        anchors.bottom: parent.bottom ; anchors.bottomMargin:25
        anchors.horizontalCenter: parent.horizontalCenter

        delegate: Rectangle {
              implicitWidth: 8
              implicitHeight: 8

              radius: width / 2
              color: "#ffffff"

              opacity: index === control.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

              Behavior on opacity {
                  OpacityAnimator {
                      duration: 100
                  }
              }
              MouseArea {
                anchors.fill: parent
                onClicked: grid.currentIndex = index*6

              }
          }

    }
    // page indicator quadrato
    PageIndicator {
        id: control1
        visible: true
        interactive: false
        count: myModel.numIndicatori
        currentIndex: Math.floor(grid.currentIndex/6)
        anchors.bottom: parent.bottom ; anchors.bottomMargin:25
        anchors.horizontalCenter: parent.horizontalCenter

        delegate: Rectangle {
              implicitWidth: 25
              implicitHeight: 25

              //radius: width / 2
              color: "#ffffff"

              opacity: index === control1.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

              Text{

               anchors.centerIn: parent
               text:(index+1).toString()
               color: "#465775"
              }

              Behavior on opacity {
                  OpacityAnimator {
                      duration: 100
                  }
              }
              MouseArea {
                anchors.fill: parent
                onClicked: grid.currentIndex = index*6

              }
          }

    }

    CheckBox {
           text: qsTr("Mostra solo ricetteUtente")
           checked: myModelFiltrato.showOnlyUserRic
           onClicked: {
               myModelFiltrato.showOnlyUserRic = !myModelFiltrato.showOnlyUserRic

           }
           anchors.left: parent.left; anchors.leftMargin: 15
           anchors.bottom: parent.bottom ; anchors.bottomMargin: 15
    }

}
