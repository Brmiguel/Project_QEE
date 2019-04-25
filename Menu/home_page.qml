import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtCharts 2.3
import QtQuick.Layouts 1.3


Item{
 id: home_page
 property bool graph_p: false
 property bool graph_V: false
 property bool graph_I: false

     Flickable {
        id: home_page_f

         anchors.fill: parent
         anchors.topMargin: overlayHeader.height
         anchors.leftMargin: !inPortrait ? drawer.width : undefined

         topMargin: 20
         bottomMargin: 20
         contentHeight: home_page_column.height + title.height + textPrice.height

         StackLayout {

              width:home_page_f.width
              height:home_page_f.height
              id: home_layout
              //currentIndex:0
              currentIndex:(bluetooth.password && bluetooth.ledConnec)?1:0;

              GridLayout{
                  columns:3

                  ColumnLayout{
                  }
                  ColumnLayout{
                      id:home_column
                      Label {
                          Layout.preferredHeight: home_page_f.height/3
                      }
                      Label{
                          id : home_page_status
                          font.pixelSize: 12
                          text:bluetooth.ledConnec?"Palavra-passe Errada":"Medidor não esta conectado!"
                          Layout.preferredHeight: home_page_f.height/5
                          Layout.alignment: Qt.AlignCenter

                      }
                  }
                  ColumnLayout{
                  }
              }
            }
             Label {
                 id: title
                 font.pixelSize: 22
                 anchors.top: parent.top
                 anchors.left: parent.left
                 anchors.right: parent.right
                 width: parent.width
                 elide: Label.ElideRight
                 horizontalAlignment: Qt.AlignHCenter
                 text: qsTr("Pagina Inicial")
             }

             Label {
                 visible:(home_layout.currentIndex==1)?true:false
                 id : textPrice
                 anchors.topMargin: 20
                 anchors.top: title.bottom
                 anchors.left: parent.left
                 anchors.leftMargin: 40
                 width: parent.width
                 wrapMode: Label.WordWrap
                 text: bluetooth.paymentText
            }


             Column {
                 visible:(home_layout.currentIndex==1)?true:false
                 id: home_page_column
                 spacing: 20
                 anchors.margins: 20
                 anchors.top: textPrice.bottom
                 anchors.left: parent.left
                 anchors.right: parent.right

                 Timer {
                       interval: 500; running: true; repeat: true
                       onTriggered: potenciaRealTime.rotation
                 }

                 ChartView {

                     id: potenciaRealTime
                     title:"Potência em tempo real"
                     width:inPortrait ? window.width : parent.width
                     height:inPortrait ? window.width : parent.width
                     legend.alignment: Qt.AlignBottom
                     theme: ChartView.ChartThemeLight
                     antialiasing: true


                     Timer {
                           interval: 500; running: true; repeat: true
                           onTriggered: {

                               for(var i = 0;i < 25;i ++) {
                                   if (graph_p)
                                        seriesPotencia.remove(i);
                                   seriesPotencia.insert(i,i, bluetooth.get_Rt_P(i));

                               }
                               graph_p =true;
                           }
                     }

                     LineSeries {

                         name: "Potência Gasta "
                         id : seriesPotencia
                         axisX: ValueAxis {
                                         min: 0
                                         max:25
                                         tickInterval : 5
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }

                         axisY: ValueAxis {
                                         min: 0
                                         max:50
                                         tickInterval : 10
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }



                     }
                 }

                 ChartView {

                     id: currentRealTime
                     title:"Corrente em tempo real"
                     width:inPortrait ? window.width : parent.width
                     height:inPortrait ? window.width : parent.width
                     legend.alignment: Qt.AlignBottom
                     theme: ChartView.ChartThemeLight
                     antialiasing: true

                     Timer {
                           interval: 500; running: true; repeat: true
                           onTriggered: {

                               for(var i = 0;i < 25;i ++) {
                                   if (graph_I)
                                        seriesCorrente.remove(i);
                                   seriesCorrente.insert(i,i, bluetooth.get_Rt_I(i));

                               }
                               graph_I =true;
                           }
                     }

                     LineSeries {

                         name: "Corrente "
                         id : seriesCorrente
                         axisX: ValueAxis {
                                         min: 0
                                         max:25
                                         tickInterval : 5
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }

                         axisY: ValueAxis {
                                         min: 0
                                         max:50
                                         tickInterval : 10
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }



                     }
                 }


                 ChartView {

                     id: voltageRealTime
                     title:"Tensão em tempo real"
                     width:inPortrait ? window.width : parent.width
                     height:inPortrait ? window.width : parent.width
                     legend.alignment: Qt.AlignBottom
                     theme: ChartView.ChartThemeLight
                     antialiasing: true

                     Timer {
                           interval: 500; running: true; repeat: true
                           onTriggered: {

                               for(var i = 0;i < 25;i ++) {
                                   if (graph_V)
                                        seriesVoltage.remove(i);
                                   seriesVoltage.insert(i,i, bluetooth.get_Rt_V(i));

                               }
                               graph_V =true;
                           }
                     }

                     LineSeries {

                         name: "Tensão "
                         id : seriesVoltage
                         axisX: ValueAxis {
                                         min: 0
                                         max:25
                                         tickInterval : 5
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }

                         axisY: ValueAxis {
                                         min: 0
                                         max:50
                                         tickInterval : 10
                                         tickType:ValueAxis.TicksDynamic
                                         labelFormat: "%.0f"
                         }



                     }
                 }




             }

         ScrollIndicator.vertical: ScrollIndicator { }
    }

}
