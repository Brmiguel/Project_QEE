import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import bluetooth 1.0


ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("FUCK QEE")

    Bluetooth{

        id:bluetooth

    }

    //verifica se esta portrait ou nao, vendo de a altura é maior que a largura
    readonly property bool inPortrait: window.width < window.height

    /*Grafico Potencia geral*/
    property real p_P: 400
    property real p_Q: 100
    property real p_S: p_P+p_Q

    /*Grafico ano*/
    property real graf_year_Year:2018
    property var graf_year_P:[490,450,500,600,455,340,200,230,200,340,450,670]
    property var graf_year_Q:[150,160,80,123,50,100,138,150,100,80,67,180]

    /*Grafico mês*/
    property real graf_month_Month:1
    property var graf_month_P:[]
    property var graf_month_Q:[]

    /*Grafico dia*/
    property real graf_day_Day:1
    property var graf_day_P:[]
    property var graf_day_Q:[]

    /*Grafico Falha*/
    property string graf_fault_last:"Sag"
    property var graf_fault_V:[]
    property var graf_fault_Time:[]
    property real graf_fault_Sag:0
    property real graf_fault_Swell:0


    /*Grafico Tempo Real*/
    property var graf_rt_V:[]
    property var graf_rt_I:[]
    property var graf_rt_P:[]
    property var graf_rt_Time:[]


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
