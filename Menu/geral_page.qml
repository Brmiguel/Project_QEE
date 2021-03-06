import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item{
 id: geral_page

 Flickable {
     id: geral_page_f

     anchors.fill: parent
     anchors.topMargin: overlayHeader.height
     anchors.leftMargin: !inPortrait ? drawer.width : undefined

     topMargin: 20
     bottomMargin: 20
     contentHeight: geral_page_column.height

     Column {
         id: geral_page_column
         spacing: 20
         anchors.margins: 20
         anchors.left: parent.left
         anchors.right: parent.right

         Label {
             font.pixelSize: 22
             width: parent.width
             elide: Label.ElideRight
             horizontalAlignment: Qt.AlignHCenter
             text: qsTr("Pagina Geral")
         }

         Label {
             width: parent.width
             wrapMode: Label.WordWrap
             text: qsTr("Olá estas na pagina geral no modo ").arg(inPortrait ? qsTr("portrait") : qsTr("landscape"))
         }
     }

     ScrollIndicator.vertical: ScrollIndicator { }
 }

}
