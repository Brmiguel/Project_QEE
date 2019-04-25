import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtCharts 2.3
import bluetooth 1.0



Item{
 id: graficos_page

 Flickable {
     id: graficos_page_f

     anchors.fill: parent
     anchors.topMargin: overlayHeader.height
     anchors.leftMargin: !inPortrait ? drawer.width : undefined

     topMargin: 20
     bottomMargin: 20
     contentHeight: graficos_page_column.height

     Column {
         id: graficos_page_column
         spacing: 20
         anchors.margins: 20
         anchors.left: parent.left
         anchors.right: parent.right

         Label {
             font.pixelSize: 22
             width: parent.width
             elide: Label.ElideRight
             horizontalAlignment: Qt.AlignHCenter
             text: qsTr("Pagina Grafico")
         }

         ChartView {

             title: "Potencia Total"
             legend.visible: true
             legend.alignment: Qt.AlignBottom
             width:inPortrait ? parent.width : parent.width
             height:inPortrait ? parent.width :window.height/1.5

             theme: ChartView.ChartThemeLight
             antialiasing: true
             animationDuration:5
             //animationEasingCurve :Easing.Linear
             animationOptions:ChartView.AllAnimations

             PieSeries {
                    id: potencia_S
                    size: 1
                    holeSize: 0.7
                    PieSlice { label: "Potencia Aparente"; value:(bluetooth.graf_P_P + bluetooth.graf_P_Q); color: "#fb8c00" }
             }
             PieSeries {
                 size: 0.7
                 holeSize: 0.25
                 id: potencia_P_Q
                 horizontalPosition : inPortrait ? 0.5:0.5
                 PieSlice { label: "Potencia Ativa"; value: bluetooth.graf_P_P ; color: "#ffb300" }
                 PieSlice { label: "Potencia Reativa"; value: bluetooth.graf_P_Q ; color: "#f4511e"}
             }
         }

         ChartView {

             id:ano_g
             title:"Ano: "+bluetooth.graf_year
             width:inPortrait ? window.width : parent.width
             height:inPortrait ? window.width : parent.width
             legend.alignment: Qt.AlignBottom
             theme: ChartView.ChartThemeLight
             antialiasing: true

             HorizontalBarSeries {
                 axisY: BarCategoryAxis { labelsFont:(ano_g.height<400)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8}) ;categories: ["1/"+bluetooth.graf_year, "2/"+bluetooth.graf_year,"3/"+bluetooth.graf_year, "4/"+bluetooth.graf_year,"5/"+bluetooth.graf_year, "6/"+bluetooth.graf_year,"7/"+bluetooth.graf_year,"8/"+bluetooth.graf_year, "9/"+bluetooth.graf_year ,"10/"+bluetooth.graf_year,"11/"+bluetooth.graf_year, "12/"+bluetooth.graf_year] }
                 axisX: ValueAxis {
                                 min: 0
                                 max:bluetooth.graf_year_Scale
                                 tickInterval : (bluetooth.graf_year_Scale/14)-(bluetooth.graf_year_Scale/14)%10
                                 tickType:ValueAxis.TicksDynamic
                                 labelFormat: "%.0f"
                                 labelsFont:(ano_g.width<500)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8})
                 }
                 BarSet { id:graf_year_P;label: "Potencia Ativa" ; values:bluetooth.graf_year_P}
                 BarSet { id:graf_year_Q;label: "Potencia Reativa"; values:bluetooth.graf_year_Q}

             }
         }

         ChartView {

             id:month_g
             title:"Mês: "+bluetooth.graf_month
             width:inPortrait ? window.width : parent.width
             height:inPortrait ? window.width+window.width/1.2 : window.height+window.width/2
             legend.alignment: Qt.AlignBottom
             antialiasing: true
             theme: ChartView.ChartThemeLight

             HorizontalBarSeries {
                 axisY: BarCategoryAxis { labelsFont:(month_g.width<440)?Qt.font({pointSize: 5}):Qt.font({pointSize: 7}) ;categories: bluetooth.graf_month_D }
                 axisX: ValueAxis {
                                 min: 0
                                 max:bluetooth.graf_month_Scale
                                 tickInterval :5
                                 tickType:ValueAxis.TicksDynamic
                                 labelFormat: "%.0f"
                                 //labelsFont:(month_g.width<500)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8})
                 }
                 BarSet { id:graf_month_P;label: "Potencia Ativa" ; values:bluetooth.graf_month_P}
                 BarSet { id:graf_month_Q;label: "Potencia Reativa"; values:bluetooth.graf_month_Q}

             }
         }

         ChartView {

             id:day_g
             title:"Dia: "+bluetooth.graf_day
             width:inPortrait ? window.width : parent.width
             height:inPortrait ? window.width+window.width/2: window.height+window.width/3
             legend.alignment: Qt.AlignBottom
             theme: ChartView.ChartThemeLight
             antialiasing: true

             HorizontalBarSeries {
                 axisY: BarCategoryAxis { labelsFont:(day_g.width<440)?Qt.font({pointSize: 5}):Qt.font({pointSize: 7}) ;categories:["0h","1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h","13h","14h","15h","16h","17h","18h","19h","20h","21h","22h","23h"]}
                 axisX: ValueAxis {
                                 min: 0
                                 max:bluetooth.graf_day_Scale
                                 tickInterval:2
                                 tickType:ValueAxis.TicksDynamic
                                 labelFormat: "%.0f"
                                 labelsFont:(day_g.width<500)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8})
                 }
                 BarSet { id:graf_day_P;label: "Potencia Ativa" ; values:bluetooth.graf_day_P}
                 BarSet { id:graf_day_Q;label: "Potencia Reativa"; values:bluetooth.graf_day_Q}

             }
         }


         Component.onCompleted: {
             // Set the common slice properties dynamically for convenience
             for (var i = 0; i < potencia_S.count; i++) {
                 potencia_S.at(i).labelPosition = PieSlice.LabelOutside;
                 potencia_S.at(i).labelVisible = true;
                 potencia_S.at(i).borderWidth = 3;
             }
             for (i = 0; i < potencia_P_Q.count; i++) {
                 potencia_P_Q.at(i).borderWidth = 2;
             }

         }


     }

     ScrollIndicator.vertical: ScrollIndicator { }
    }

}
