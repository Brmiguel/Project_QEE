import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4


Item{
 id: geral_page

 Flickable {
     ScrollIndicator.vertical: ScrollIndicator { }

     id: con_page_f

     anchors.fill: parent
     anchors.topMargin: overlayHeader.height
     anchors.leftMargin: !inPortrait ? drawer.width : undefined

     topMargin: 20
     bottomMargin: 20

     StackLayout {
         width:con_page_f.width
         height:con_page_f.height

         id: layout
         currentIndex: 1
         Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
         GridLayout{
             columns:3
             ColumnLayout{
             }
             ColumnLayout{
                 id:setting_pass_column
                 Label {
                     Layout.preferredHeight: con_page_f.height/3
                 }
                 Label{
                     id : title_passe
                     font.pixelSize: 18

                     text: qsTr("Palavra-passe:")
                 }
                 TextField{
                    id:pass_field
                    Layout.preferredWidth:setting_pass_column.width/1.5
                    echoMode:TextInput.Password
                    placeholderText:"Introduza a Palavra-passe:"
                    background: Rectangle {
                           id:pass_field_back
                           color:"#F42E2E"
                           border.color: "black"
                       }
                    onFocusChanged:{
                        pass_field_back.color="transparent"
                    }
                 }
                 Button{
                    id:button_pass
                    text:"Entrar"
                    Layout.preferredWidth: setting_pass_column.width/1.5
                    onClicked: {

                    }
                 }
             }
             ColumnLayout{
             }
         }


         GridLayout{
             columns:3
             ColumnLayout{
             }
             ColumnLayout{
                 id:setting_column
                 spacing: 25
                 Label{
                     id : title_conf
                     font.pixelSize: 22
                     Layout.alignment: Qt.AlignCenter
                     text: qsTr("Configurações")
                 }
                  ColumnLayout{
                      Layout.alignment: Qt.AlignCenter

                     Label{
                         id : title_change_pass
                         font.pixelSize: 18
                         Layout.alignment: Qt.AlignCenter
                         text: qsTr("Mudar a Palavra-passe:")
                     }
                     TextField{
                        id:change_pass_field
                        echoMode:TextInput.Password
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: setting_column.width/1.5
                        placeholderText:"Nova Palavra-passe:"
                        background: Rectangle {
                               id:change_pass_field_back
                               border.color: "black"
                           }
                        onFocusChanged:{
                        }
                     }
                     Button{
                        id:button_change_pass
                        text:"Mudar"
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: setting_column.width/1.5
                        onClicked: {

                        }
                     }
                 }
                  ColumnLayout{
                      Layout.alignment: Qt.AlignCenter
                     Label{
                         id : title_price
                         font.pixelSize: 18
                         Layout.alignment: Qt.AlignCenter
                         text: qsTr("Mudar o preço da luz:")
                     }
                     TextField{
                        id:change_price
                        Layout.preferredWidth: setting_column.width/1.5
                        placeholderText:"Novo Preço:"
                        Layout.alignment: Qt.AlignCenter
                        background: Rectangle {
                               id:change_price_field_back
                               border.color: "black"
                           }
                        onFocusChanged:{
                        }
                     }
                     Button{
                        id:button_change_price
                        Layout.alignment: Qt.AlignCenter
                        text:"Mudar"
                        Layout.preferredWidth: setting_column.width/1.5
                        onClicked: {

                        }
                     }
                 }

                  ColumnLayout{
                      Layout.alignment: Qt.AlignCenter

                     Label{
                         id : title_Date
                         Layout.alignment: Qt.AlignCenter
                         font.pixelSize: 18
                         text: qsTr("Enviar data atual")
                     }
                     Button{
                        id:button_Date
                        Layout.alignment: Qt.AlignCenter
                        text:"Enviar"
                        Layout.preferredWidth: setting_column.width/1.5
                        onClicked: {

                        }
                     }
                 }

                  ColumnLayout{
                      Layout.alignment: Qt.AlignCenter

                     Label{
                         id : title_Turn_Light
                         Layout.alignment: Qt.AlignCenter
                         font.pixelSize: 18
                         text: qsTr("Desligar/Ligar Luz")
                     }
                     Button{
                        id:button_Light
                        Layout.alignment: Qt.AlignCenter
                        text:"Desligar" //depois verificar variavel no codigo
                        Layout.preferredWidth: setting_column.width/1.5
                        onClicked: {

                        }
                     }
                 }
             }
             ColumnLayout{
             }

         }
     }

 }

}
