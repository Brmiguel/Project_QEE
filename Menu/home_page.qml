import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtCharts 2.3

Item{
 id: home_page
 property bool graph_p: false
     Flickable {
        id: home_page_f

         anchors.fill: parent
         anchors.topMargin: overlayHeader.height
         anchors.leftMargin: !inPortrait ? drawer.width : undefined

         topMargin: 20
         bottomMargin: 20
         contentHeight: home_page_column.height + title.height + ledConnected.height + textPrice.height

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
                 id : textPrice
                 anchors.topMargin: 20
                 anchors.top: title.bottom
                 anchors.left: parent.left
                 anchors.leftMargin: 40
                 width: parent.width
                 wrapMode: Label.WordWrap
                 text: bluetooth.paymentText
            }

             Image{

                 id: ledConnected
                 width: 40
                 height: 40
                 source: bluetooth.ledConnec ? "Imagens/led_on.png" :
                                    "Imagens/led_off.png"

                 anchors.top: parent.top
                 anchors.right :parent.right

             }

             Column {
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
                                        series.remove(i);
                                   series.insert(i,i, bluetooth.get_Rt_P(i));

                               }
                               graph_p =true;
                           }
                     }

                     LineSeries {

                         name: "Potência Gasta "
                         id : series
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

                     LineSeries {
                         name: "Corrente"
                        XYPoint { x: 1; y: bluetooth.graf_rt_I }
                        XYPoint { x: 2; y: bluetooth.graf_rt_I }
                        XYPoint { x: 3; y: bluetooth.graf_rt_I }
                        XYPoint { x: 4; y: bluetooth.graf_rt_I }
                        XYPoint { x: 5; y: bluetooth.graf_rt_I }
                        XYPoint { x: 6; y: bluetooth.graf_rt_I }
                        XYPoint { x: 7; y: bluetooth.graf_rt_I }
                        XYPoint { x: 8; y: bluetooth.graf_rt_I }
                        XYPoint { x: 9; y: bluetooth.graf_rt_I }
                        XYPoint { x: 10; y: bluetooth.graf_rt_I }
                        XYPoint { x: 11; y: bluetooth.graf_rt_I }
                        XYPoint { x: 12; y: bluetooth.graf_rt_I }
                        XYPoint { x: 13; y: bluetooth.graf_rt_I }
                        XYPoint { x: 14; y: bluetooth.graf_rt_I }
                        XYPoint { x: 15; y: bluetooth.graf_rt_I }
                        XYPoint { x: 16; y: bluetooth.graf_rt_I }
                        XYPoint { x: 17; y: bluetooth.graf_rt_I }
                        XYPoint { x: 18; y: bluetooth.graf_rt_I }
                        XYPoint { x: 19; y: bluetooth.graf_rt_I }
                        XYPoint { x: 20; y: bluetooth.graf_rt_I }
                        XYPoint { x: 21; y: bluetooth.graf_rt_I }
                        XYPoint { x: 22; y: bluetooth.graf_rt_I }
                        XYPoint { x: 23; y: bluetooth.graf_rt_I }
                        XYPoint { x: 24; y: bluetooth.graf_rt_I }
                        XYPoint { x: 25; y: bluetooth.graf_rt_I }
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

                     LineSeries {
                         name: "Tensão"
                         XYPoint { x: 1; y: bluetooth.graf_rt_V }
                         XYPoint { x: 2; y: bluetooth.graf_rt_V }
                         XYPoint { x: 3; y: bluetooth.graf_rt_V }
                         XYPoint { x: 4; y: bluetooth.graf_rt_V }
                         XYPoint { x: 5; y: bluetooth.graf_rt_V }
                         XYPoint { x: 6; y: bluetooth.graf_rt_V }
                         XYPoint { x: 7; y: bluetooth.graf_rt_V }
                         XYPoint { x: 8; y: bluetooth.graf_rt_V }
                         XYPoint { x: 9; y: bluetooth.graf_rt_V }
                         XYPoint { x: 10; y: bluetooth.graf_rt_V }
                         XYPoint { x: 11; y: bluetooth.graf_rt_V }
                         XYPoint { x: 12; y: bluetooth.graf_rt_V }
                         XYPoint { x: 13; y: bluetooth.graf_rt_V }
                         XYPoint { x: 14; y: bluetooth.graf_rt_V }
                         XYPoint { x: 15; y: bluetooth.graf_rt_V }
                         XYPoint { x: 16; y: bluetooth.graf_rt_V }
                         XYPoint { x: 17; y: bluetooth.graf_rt_V }
                         XYPoint { x: 18; y: bluetooth.graf_rt_V }
                         XYPoint { x: 19; y: bluetooth.graf_rt_V }
                         XYPoint { x: 20; y: bluetooth.graf_rt_V }
                         XYPoint { x: 21; y: bluetooth.graf_rt_V }
                         XYPoint { x: 22; y: bluetooth.graf_rt_V }
                         XYPoint { x: 23; y: bluetooth.graf_rt_V }
                         XYPoint { x: 24; y: bluetooth.graf_rt_V }
                         XYPoint { x: 25; y: bluetooth.graf_rt_V }
                     }
                 }




             }

         ScrollIndicator.vertical: ScrollIndicator { }
    }

}
