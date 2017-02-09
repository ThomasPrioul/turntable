import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0

Item {
    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        rowSpacing: 10
        columnSpacing: 10
        flow: width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom

        Item {
            id: leftPaneRoot
            Layout.fillWidth: true
            Layout.fillHeight: true

            Pane {
                id: leftPane
                padding: 0
                anchors.fill: parent
                Material.elevation: 6

                ColumnLayout {
                    anchors.fill: parent

                    ToolBar {
                        padding: 12
                        Layout.fillWidth: true
                        Material.elevation : 0

                        Label {
                            text: qsTr("Turntable state")
                            anchors.fill: parent
                            font.pointSize: 12
                            font.bold: true
                        }
                    }

                    Pane {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        // Here goes turntable rotating object
                        BusyIndicator {
                            id: resetIndicator
                            visible: app.turntable.resetting
                        }
                    }

                    // Horizontal line
                    Rectangle {
                        height: 1
                        Layout.fillWidth: true
                        color: Material.foreground
                        opacity: 0.5
                    }

                    Pane {
                        topPadding: 3
                        padding: 6
                        Layout.fillWidth: true
                        enabled: !app.turntable.busy

                        RowLayout {
                            Button {
                                text: qsTr("Reset")
                                onClicked: app.turntable.reset();
                            }

                            Button {
                                text: qsTr("Stop")
                                onClicked: {
                                    app.turntable.stop();
                                }
                            }
                        }
                    }
                }
            }
        }

        Item {
            id: rightPaneRoot
            Layout.fillWidth: true
            Layout.fillHeight: true

            Pane {
                id : rightPane
                padding: 0
                anchors.fill: parent
                Material.elevation: 6

                ColumnLayout {
                    anchors.fill: parent

                    ToolBar {
                        padding: 12
                        Layout.fillWidth: true
                        Material.elevation : 0

                        Label {
                            text: qsTr("Tracks")
                            anchors.fill: parent
                            font.pointSize: 12
                            font.bold: true
                        }
                    }

                    Pane {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ListView {
                            id : tracksList
                            anchors.fill: parent
                            snapMode: ListView.SnapToItem
                            boundsBehavior: Flickable.StopAtBounds
                            spacing: 10
                            model: app.turntable.tracksData.list
                            delegate: TrackItemDelegate { }
                        }
                    }

                    // Horizontal line
                    Rectangle {
                        height: 1
                        Layout.fillWidth: true
                        color: Material.foreground
                        opacity: 0.5
                    }

                    Pane {
                        topPadding: 3
                        padding: 6
                        Layout.fillWidth: true
                        enabled: !app.turntable.busy

                        RowLayout {
                            Button {
                                text: qsTr("Add track")
                                onClicked: {
                                    app.turntable.tracksData.addTrack(qsTr("New track"), 0);
                                }
                            }

                            Button {
                                text: qsTr("Get config")
                                onClicked: app.turntable.getConfig();
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
Grid {
    columns: 2
    rows: 1
    id: rowLayout
    spacing: 10
    anchors.margins: 20
    anchors.fill: parent

    Item {
        id: turntableBox
        width: parent.width / parent.columns
        height: parent.height / parent.rows

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: qsTr("Turntable")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
                font.pointSize: 16
            }

            Image {
                Layout.fillHeight: true
                Layout.fillWidth: true
                fillMode: Image.PreserveAspectFit
                source: "qrc:/images/track.png"
            }

            ToolBar {
                id: turntableCommands
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent
                    spacing: 20

                    ToolButton {
                        contentItem: Text {
                            text: "◀️"
                            font.pointSize: 16
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                        }
                    }

                    Label {
                        id: turntableAngle
                        text: "102°"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 16
                    }

                    ToolButton {
                        contentItem: Text {
                            text: "▶️"
                            font.pointSize: 16
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                        }
                    }
                }
            }
        }
    }

    Item {
        id: tracksBox
        width: parent.width / parent.columns
        height: parent.height / parent.rows

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Label {
                    text: qsTr("Tracks")
                    font.bold: true
                    font.pointSize: 16
                }
            }


        }
    }
}
*/
