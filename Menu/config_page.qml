import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import bluetooth 1.0



Item{
 id: geral_page

 Flickable {
     anchors.fill: parent
     flickableDirection: Flickable.VerticalFlick
     boundsBehavior: Flickable.DragOverBounds
     clip: true
     contentHeight: 500
     id: con_page_f
     anchors.topMargin: overlayHeader.height
     anchors.leftMargin: !inPortrait ? drawer.width : undefined
     topMargin: 20
     bottomMargin: 20

     StackLayout {
         width:con_page_f.width
         height:con_page_f.height

         id: layout
         //currentIndex:(bluetooth.password && bluetooth.ledConnec)?1:0;
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
                    echoMode:TextInput.Password
                    placeholderText:"Introduza a Palavra-passe:"
                    background: Rectangle {
                           id:pass_field_back
                           color:{
                               if(!bluetooth.password && bluetooth.password_index>0)
                                color= "#F42E2E";
                               else
                                color="transparent";
                           }
                           border.color: "black"
                       }
                    onFocusChanged:{
                        pass_field_back.color="transparent"
                    }
                 }
                 Button{
                    id:button_pass
                    text:"Entrar"
                    Layout.preferredWidth: pass_field.width
                    onClicked: {
                        bluetooth.send(pass_field.text,1,false);
                        pass_status.text=bluetooth.ledConnec?"":"Medidor não esta conectado!";
                        pass_field_back.color="transparent"

                    }
                 }
                 Label{
                     id : pass_status
                     font.pixelSize: 12
                     text:(!bluetooth.password && bluetooth.password_index>0)? qsTr("Palavra passe errada!"):qsTr("")
                     Layout.preferredHeight: con_page_f.height/5
                     Layout.alignment: Qt.AlignCenter

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
                            Bluetooth.mudar_preco(change_price.text);

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

                     Timer {
                           interval: 500; running: true; repeat: true
                           onTriggered: time.text = Qt.formatDateTime(new Date(),"dd.MM.yyyy ")+"-"+Qt.formatTime(new Date()," hh:mm:ss");
                     }
                     Text {
                         id: time
                         Layout.alignment: Qt.AlignCenter
                         //font.pixelSize: Theme.fontSizeHuge * 2.0
                     }
                     Button{
                        id:button_Date
                        Layout.alignment: Qt.AlignCenter
                        text:"Enviar"
                        Layout.preferredWidth: setting_column.width/1.5
                        onClicked: {
                             bluetooth.send(time.text,4,false);
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
     ScrollIndicator.vertical: ScrollIndicator { }

 }

}
