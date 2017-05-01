import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0
import "TurntableViewScript.js" as TurntableScript

Item {
    id : turntableViewRoot

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

                    // Header
                    ToolBar {
                        padding: 0
                        Layout.fillWidth: true
                        Material.elevation : 0

                        RowLayout {
                            anchors.fill: parent
                            spacing: 0

                            Label {
                                text: qsTr("Turntable state")
                                padding: 12
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                font.pointSize: 12
                                font.bold: true
                            }

                            BusyIndicator {
                                id: resetIndicator
                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 40
                                padding: 6
                                visible: app.turntable.busy
                            }
                        }
                    }

                    Pane {
                        id: turntableStatePane
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        ColumnLayout {
                            id: turntableViewerLayout
                            visible: !app.turntable.resetting && app.turntable.nbSteps !== -1
                            anchors.fill: parent

                            // Visual representation
                            Item {
                                id: turntableImageContainer
                                Layout.fillHeight: true
                                Layout.fillWidth: true

                                Image {
                                    id: turntableImage
                                    antialiasing: true
                                    anchors.centerIn: parent
                                    width: Math.min(447, parent.height <= parent.width ? parent.height : parent.width)
                                    source: "qrc:/images/track.png"
                                    fillMode: Image.PreserveAspectFit
                                    rotation: app.turntable.nbSteps === -1 ? 0 : app.turntable.position / app.turntable.nbSteps * -360.0 // Angle interpreted as clockwise so need reverse
                                }

                                Item {
                                    id: turntableTrackImagesContainer
                                    anchors.centerIn: parent
                                    height: turntableImage.height
                                    width: turntableImage.width

                                    Connections {
                                        target: app.turntable
                                        onStepsChanged: {
                                            TurntableScript.loaded = true;
                                            TurntableScript.loadItems(turntableTrackImagesContainer);
                                        }
                                    }

                                    Connections {
                                        target: app.turntable
                                        onPositionChanged: {
                                            if (!TurntableScript.loaded) return;
                                            TurntableScript.setOccupiedTracks(turntableTrackImagesContainer);
                                        }
                                    }

                                    Connections {
                                        target: app.turntable.tracksData
                                        onListChanged: {
                                            if (!TurntableScript.loaded) return;
                                            TurntableScript.loadItems(turntableTrackImagesContainer);
                                        }
                                    }
                                }

                                Label {
                                    text: app.turntable.nbSteps === -1 ? "unknown" : (app.turntable.position / app.turntable.nbSteps * 360.0).toFixed(2) + "° (" + app.turntable.position + ")"
                                    anchors.left: parent.left
                                    anchors.leftMargin: 0
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: 0
                                    Layout.fillWidth: true

                                }
                            }

                            // Resetting message
                            ColumnLayout {
                                id: resetPane
                                anchors.right: parent.right
                                anchors.rightMargin: 0
                                anchors.left: parent.left
                                anchors.leftMargin: 0
                                anchors.verticalCenter: parent.verticalCenter
                                visible: app.turntable.resetting

                                Label {
                                    text: qsTr("Resetting turntable...")
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }

                                ProgressBar {
                                    id: progressBar
                                    Layout.fillWidth: true
                                    indeterminate: true
                                }
                            }
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

                        RowLayout {
                            Button {
                                text: qsTr("Left")
                                onPressed: app.turntable.startIndefiniteMove(true)
                                onReleased: app.turntable.stop()
                            }

                            Button {
                                text: qsTr("Right")
                                onPressed: app.turntable.startIndefiniteMove(false)
                                onReleased: app.turntable.stop()
                            }

                            Button {
                                text: qsTr("Reset")
                                onClicked: app.turntable.reset();
                                enabled: !app.turntable.busy
                            }

                            Button {
                                text: qsTr("Stop")
                                onClicked: {
                                    app.turntable.stop();
                                }

                                enabled: app.turntable.busy && !app.turntable.resetting
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
                            clip: true
                            anchors.fill: parent
                            snapMode: ListView.SnapToItem
                            boundsBehavior: Flickable.StopAtBounds
                            spacing: 10
                            model: app.turntable.tracksData.list
                            delegate: TrackItemDelegate {
                                clip: true
                                width: tracksList.width
                                height: 50
                                onEditClicked: {
                                    newTrackNameField.text = name
                                    newTrackPositionField.text = position
                                    newTrackRelayCheckBox.checked = relay
                                    addTrackPopup.open()
                                }
                            }
                        }
                    }

                    // Horizontal line
                    Rectangle {
                        height: 1
                        anchors.topMargin: 10
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
                                    addTrackPopup.open();
                                    //app.turntable.tracksData.addTrack(qsTr("New track"), 0);
                                }
                            }

                            Button {
                                text: qsTr("Get config")
                                onClicked: app.turntable.getConfig();
                            }

                            Button {
                                text: qsTr("Go to position")
                                onClicked: goToPositionMenu.open();

                                Menu {
                                    id: goToPositionMenu
                                    transformOrigin: Menu.Top
                                    onVisibleChanged: {
                                        if (visible) {
                                            goToPositionTextField.clear()
                                        }
                                    }

                                    Item {
                                        anchors.fill: parent

                                        RowLayout {
                                            anchors.margins: 10
                                            anchors.fill: parent
                                            TextField {
                                                id : goToPositionTextField
                                                Layout.fillWidth: true
                                                placeholderText: qsTr("Position")
                                            }
                                            Button {
                                                text: qsTr("Go!")
                                                onClicked: {
                                                    app.turntable.moveToPosition(goToPositionTextField.text);
                                                    goToPositionMenu.close();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Popup {
            id: addTrackPopup
            x: Math.max(0, window.width/2 - addTrackPopup.implicitWidth)
            y: Math.max(0, window.getHeight()/2 - addTrackPopup.implicitHeight/2)
            width: 2*implicitWidth
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            ColumnLayout {
                width: parent.width
                Label {
                    text: qsTr("Create/edit a track")
                    font.pointSize: 12
                    font.bold: true
                    Layout.fillWidth: true
                }

                TextField {
                    id: newTrackNameField
                    placeholderText: qsTr("Name of the track")
                    Layout.fillWidth: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    TextField {
                        id: newTrackPositionField
                        placeholderText: qsTr("Position of the track")
                        Layout.fillWidth: true
                        validator: IntValidator { bottom: 0; top: (app.turntable.nbSteps - 1) }
                    }

                    Button {
                        text: qsTr("Current")
                        onClicked: newTrackPositionField.text = app.turntable.position.toString();
                    }
                }

                RowLayout{
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Relay polarization of the way")
                        font.pointSize: 8
                        font.bold: false
                        Layout.fillWidth: true
                    }

                    CheckBox {
                        id: newTrackRelayCheckBox
                    }

                }


                Button {
                    id: newTrackValidateButton
                    text: qsTr("OK")
                    Layout.alignment: Qt.AlignRight
                    enabled: newTrackNameField.acceptableInput && newTrackPositionField.acceptableInput
                    onClicked: {
                        app.turntable.addServiceTrack(newTrackNameField.text, newTrackPositionField.text, newTrackRelayCheckBox.checked);
                        addTrackPopup.close();
                    }
                }
            }
        }

        Popup {
            id: resetFailedPopup
            x: Math.max(0, window.width/2 - resetFailedPopup.implicitWidth)
            y: Math.max(0, window.getHeight()/2 - resetFailedPopup.implicitHeight/2)
            width: implicitWidth * 2
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            ColumnLayout {
                anchors.fill: parent
                Label {
                    text: qsTr("Reset failed")
                    font.pointSize: 12
                    font.bold: true
                    Layout.fillWidth: true
                }

                Label { text: qsTr("Could not detect the position 0 indicator."); Layout.fillWidth: true; }
                Button { text: qsTr("OK"); onClicked: resetFailedPopup.close(); Layout.alignment: Qt.AlignRight; }
            }

        }

        Connections {
            target: app.turntable
            onResetDone : {
                if (!success)
                    resetFailedPopup.open();
            }
        }
    }
}
