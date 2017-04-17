import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Pane {
    anchors.bottom: parent.bottom
    anchors.top: parent.top
    width: 300
    ColumnLayout {
        id: locomotiveLayout
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Locomotive ";
                Layout.fillWidth: true;
            }
            TextField {
                id: locoIdTextField
                width: 50

                font.bold: true;

                Binding {
                    target: model
                    property: "id"
                    value: locoIdTextField.text
                }
            }

            Button {
                text: "Refresh"
                onClicked: app.locomotives.refresh(id);
            }
        }


        Switch {
            id: directionSwitch
            text: qsTr("Reverse direction")
            checked: direction

            Binding {
                target: model
                property: "direction"
                value: directionSwitch.checked
            }
        }

        RowLayout {
            Column {
                Layout.fillWidth: true
                Label {
                    text: qsTr("Speed") + " " + speed.toFixed(1)
                    bottomPadding: -8
                }
                Slider {
                    id: speedSlider
                    height: 36
                    bottomPadding: 0
                    topPadding: 0
                    from: 0
                    stepSize: 1.0
                    value: speed
                    to: 126
                    snapMode: Slider.SnapAlways

                    Binding {
                        target: model
                        property: "speed"
                        value: speedSlider.value
                    }
                }
            }

            Button {
                text: qsTr("Stop")
                onClicked: speed = 0;
            }
        }

        GridView {
            Layout.fillWidth: true
            cellHeight: 40
            cellWidth: 45
            Layout.fillHeight: true
            clip: true

            model: functionValues
            delegate: Button {
                width: 40
                height: 40
                text: id
                highlighted: functionValue
                onClicked: {
                    modelData.functionValue = !modelData.functionValue;
                }
            }
        }
    }
}
