import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtCharts 2.3


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
                    PieSlice { label: "Potencia Aparente"; value: p_aparente ; color: "#fb8c00" }
             }
             PieSeries {
                 size: 0.7
                 holeSize: 0.25
                 id: potencia_P_Q
                 horizontalPosition : inPortrait ? 0.5:0.5
                 PieSlice { label: "Potencia Ativa"; value: p_ativa ; color: "#ffb300" }
                 PieSlice { label: "Potencia Reativa"; value: p_reativa ; color: "#f4511e"}
             }
         }

         ChartView {

             id:ano_g
             title:graf_ano_Ano
             width:inPortrait ? window.width : parent.width
             height:inPortrait ? window.width : parent.width
             legend.alignment: Qt.AlignBottom
             theme: ChartView.ChartThemeLight
             antialiasing: true

             HorizontalBarSeries {
                 axisY: BarCategoryAxis { labelsFont:(ano_g.height<400)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8}) ;categories: ["1/"+graf_ano_Ano, "2/"+graf_ano_Ano,"3/"+graf_ano_Ano, "4/"+graf_ano_Ano,"5/"+graf_ano_Ano, "6/"+graf_ano_Ano,"7/"+graf_ano_Ano,"8/"+graf_ano_Ano, "9/"+graf_ano_Ano ,"10/"+graf_ano_Ano,"11/"+graf_ano_Ano, "12/"+graf_ano_Ano] }
                 axisX: ValueAxis {
                                 min: 0
                                 max:700
                                 tickInterval : 50
                                 tickType:ValueAxis.TicksDynamic
                                 labelFormat: "%.0f"
                                 labelsFont:(ano_g.width<500)?Qt.font({pointSize: 6}):Qt.font({pointSize: 8})
                 }
                 BarSet { label: "Potencia Ativa";values:graf_ano_P}
                 BarSet { label: "Potencia Reativa";values:graf_ano_Q}

             }
         }


         Component.onCompleted: {
             // Set the common slice properties dynamically for convenience
             for (var i = 0; i < potencia_S.count; i++) {
                 potencia_S.at(i).labelPosition = PieSlice.LabelOutside;
                 potencia_S.at(i).labelVisible = true;
                 potencia_S.at(i).borderWidth = 3;
             }
             for (var i = 0; i < potencia_P_Q.count; i++) {
                 potencia_P_Q.at(i).borderWidth = 2;
             }

         }


     }

     ScrollIndicator.vertical: ScrollIndicator { }
    }

}
