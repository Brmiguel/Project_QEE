import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item{
 id: home_page

 Flickable {
    id: home_page_f

     anchors.fill: parent
     anchors.topMargin: overlayHeader.height
     anchors.leftMargin: !inPortrait ? drawer.width : undefined

     topMargin: 20
     bottomMargin: 20
     contentHeight: home_page_column.height

     Column {
         id: home_page_column
         spacing: 20
         anchors.margins: 20
         anchors.left: parent.left
         anchors.right: parent.right

         Label {
             font.pixelSize: 22
             width: parent.width
             elide: Label.ElideRight
             horizontalAlignment: Qt.AlignHCenter
             text: qsTr("Pagina Inicial")
         }

         Label {
             width: parent.width
             wrapMode: Label.WordWrap
             text: qsTr("This example demonstrates how Drawer can be used as a non-closable persistent side panel.\n\n" +
                        "When the application is in portrait mode, the drawer is an interactive side panel that can " +
                        "be swiped open from the left edge. When the application is in landscape mode, the drawer " +
                        "and the content are laid out side by side.\n\nThe application is currently in %1 mode.").arg(inPortrait ? qsTr("portrait") : qsTr("landscape"))
         }
     }

     ScrollIndicator.vertical: ScrollIndicator { }
    }

}
