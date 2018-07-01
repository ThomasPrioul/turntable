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
    width: 800
    height: 432

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
            x: 0
            width: 780
            height: 412

            Label{
                text: app.turnouts.sizeLabel
                id: label
            }

            Button{
                x: 679
                y: 372
                width: 101
                height: 40
                text: "Button"
            }

            Button {
                x: 484
                y: 226
                text: "Button"
            }

            Button {
                x: 319
                y: 341
                text: "Taille"
                onClicked: {
                    app.turnouts.sizeScreen(turnoutsViewRoot.height, turnoutsViewRoot.width);
                }
            }



        }
    }

}
