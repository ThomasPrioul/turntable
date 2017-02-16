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
        Label { text: "Locomotive " + id ; Layout.fillHeight: false; Layout.fillWidth: true; font.bold: true; }

        Switch {
            text: qsTr("Reverse direction")
            checked: direction
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
