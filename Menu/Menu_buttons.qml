import QtQuick 2.9
import QtQuick.Controls 2.12


ListModel {

    ListElement {
        name: "Pagina Inicial"
        color: "transparent"
        source: "Imagens/baseline-home-24px.svg"
        pagina_id:"home_page.qml"
    }
    ListElement {
        name: "Geral"
        color: "transparent"
        source: "Imagens/baseline-view_module-24px.svg"
        pagina_id:"geral_page.qml"
    }
    ListElement {
        name: "Graficos"
        color: "transparent"
        source: "Imagens/baseline-bar_chart-24px.svg"
        pagina_id:"graficos_page.qml"
    }
    ListElement {
        name: "Configuraçoes"
        color: "transparent"
        source: "Imagens/baseline-view_module-24px.svg"
        pagina_id:"config_page.qml"
    }
    ListElement {
        name: "Conectar"
        color: "transparent"
        source: "Imagens/baseline-bluetooth_audio-24px.svg"
        pagina_id:"con_page.qml"
    }
}
