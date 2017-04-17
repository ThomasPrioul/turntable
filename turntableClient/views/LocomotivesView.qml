import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0

Item {
    id: locomotivesViewRoot
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

            ColumnLayout {
                anchors.fill: parent

                // Header
                ToolBar {
                    padding: 0
                    Layout.fillWidth: true
                    Material.elevation : 0

                    Label {
                        text: qsTr("Locomotives")
                        padding: 12
                        anchors.fill: parent
                        font.pointSize: 12
                        font.bold: true
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    ListView {
                        id: listLocomotives
                        boundsBehavior: Flickable.StopAtBounds
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 12
                        orientation: ListView.Horizontal
                        model: app.locomotives.locomotives
                        delegate: LocomotiveItemDelegate {

                        }
                    }
                }
            }
        }
        GridLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                highlighted: app.locomotives.powerActive
                text: app.locomotives.powerActive ? qsTr("Power OFF") : qsTr("Power ON")
                onClicked: {
                    if (app.locomotives.powerActive)
                        app.locomotives.powerOff();
                    else
                        app.locomotives.powerOn();
                }
            }
        }
    }
}
