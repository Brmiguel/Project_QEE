import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3


Item{
 id: conf_page






 Flickable {
    id: con_page_f

    anchors.fill: parent
    anchors.topMargin: overlayHeader.height
    anchors.leftMargin: !inPortrait ? drawer.width : undefined

    topMargin: 20
    bottomMargin: 20
    //contentHeight: con_page_column.height

    //heii

    ColumnLayout {
        id: con_page_column
        spacing: 20
        anchors.margins: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.fill: parent

        Label {
            id : title
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: parent.width
            font.pixelSize: 22
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Pagina de Conexão")
        }

        ListView {
            id: devices
            Layout.preferredHeight: 200
            Layout.preferredWidth: parent.width
            clip: true
            Layout.alignment: Qt.AlignCenter

            orientation: ListView.Vertical
            spacing: 5

            model: bluetooth.listDevice_model

            delegate: Button {
                text: model.display
                Layout.fillWidth: true
                onClicked: {
                    bluetooth.conectar(model.display);

                }
            }
        }

        TextField{
        id: mensage
        text: bluetooth.message

        }

        Button{
        id: findButton
        Layout.alignment: Qt.AlignBottom
        text: bluetooth.btnName
        onClicked: {
            bluetooth.find();

        }

        }

    }
}

}

