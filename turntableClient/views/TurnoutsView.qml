import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0

Item {
    id: turnoutsViewRoot
    anchors.fill: parent

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        rowSpacing: 10
        columnSpacing: 10

        Pane {
            enabled: !app.turntable.busy
            Layout.fillHeight: true
            Layout.fillWidth: true
            Material.elevation: 6
            padding: 0
            id: panelTurnouts

            Label{
                text: "Label"
                id: label
            }

            Button{
                x: 520
                y: 420
                text: "Button"
            }

            Button {
                x: 419
                y: 380
                text: "Button"
            }

            Button {
                x: 319
                y: 341
                text: "Taille"
                onClicked: {
                }
            }



        }
    }

}
