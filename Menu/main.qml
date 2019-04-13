import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12


ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("FUCK QEE")

    //verifica se esta portrait ou nao, vendo de a altura é maior que a largura
    readonly property bool inPortrait: window.width < window.height
    property real p_ativa: 400
    property real p_reativa: 100
    property real p_aparente: p_ativa+p_reativa

    /*Grafico ano Ano*/
    property real ano_Ano:2018
    /*Grafico ano P*/
    property real ano_P_Mes_1:490
    property real ano_P_Mes_2:450
    property real ano_P_Mes_3:500
    property real ano_P_Mes_4:600
    property real ano_P_Mes_5:455
    property real ano_P_Mes_6:340
    property real ano_P_Mes_7:200
    property real ano_P_Mes_8:230
    property real ano_P_Mes_9:200
    property real ano_P_Mes_10:340
    property real ano_P_Mes_11:450
    property real ano_P_Mes_12:670
    /*Grafico ano Q*/
    property real ano_Q_Mes_1:150
    property real ano_Q_Mes_2:160
    property real ano_Q_Mes_3:80
    property real ano_Q_Mes_4:123
    property real ano_Q_Mes_5:50
    property real ano_Q_Mes_6:100
    property real ano_Q_Mes_7:138
    property real ano_Q_Mes_8:150
    property real ano_Q_Mes_9:100
    property real ano_Q_Mes_10:80
    property real ano_Q_Mes_11:67
    property real ano_Q_Mes_12:180



        ToolBar {
            id: overlayHeader
            z: 1
            width: parent.width
            parent: window.overlay


            Label {
                id: label
                anchors.centerIn: parent
                text: "Teste"
            }
        }

        Drawer {
            id: drawer

            y: overlayHeader.height //começa depois do header
            width:inPortrait ?  window.width / 2 :  window.width / 4
            height: window.height

            modal: inPortrait
            interactive: inPortrait
            position: inPortrait ? 0 : 1
            visible: !inPortrait

            ListView {
                id: listView
                anchors.fill: parent

                headerPositioning: ListView.OverlayHeader

                header: Pane {
                    id: header_menu
                    z: 2//
                    width: parent.width

                    contentHeight: logo.height

                    Image {
                        id: logo
                        width: parent.width
                        fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad
                    }

                    MenuSeparator {
                        parent: header_menu
                        width: parent.width
                        anchors.verticalCenter: parent.bottom
                        visible: !listView.atYBeginning
                    }
                }

                footer: ItemDelegate {
                    id: footer
                    text: qsTr("Footer")
                    width: parent.width

                    MenuSeparator {
                        parent: footer
                        width: parent.width
                        anchors.verticalCenter: parent.top
                    }
                }

                model: Menu_buttons{}

                delegate: ItemDelegate {
                    text: name
                    width: parent.width
                    icon.source: source
                    icon.color: color
                    onClicked: {

                        stack.push( qsTr(pagina_id))
                    }
                }

                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }

        StackView{
            id:stack
            anchors.fill: parent
            //initialItem :Qt.resolvedUrl("home_page.qml")
            initialItem :Qt.resolvedUrl("graficos_page.qml")

        }
}
