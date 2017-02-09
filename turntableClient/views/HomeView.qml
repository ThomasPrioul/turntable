import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0

Item {
    id: root

    Label {
        id: notConnectedLabel
        text: qsTr("You are not connected.\n" +
                   "Press the ellipsis button, and then 'connect' to connect to the server.")
        wrapMode: Text.WordWrap
        font.pointSize: 12
        font.bold: true
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Item {
        id: connectedLayoutRoot
        visible: false
        anchors.fill: parent

        ColumnLayout {
            id: connectedLayout
            anchors.fill: parent
            anchors.margins: 10

            Label {
                id: connectedLabel
                text: qsTr("You're connected to the server. Explore the tabs to use the features.")

            }

            Pane {
                Material.elevation: 6
                Layout.fillHeight: true
                Layout.fillWidth: true
                padding: 0

                ColumnLayout {
                    anchors.fill: parent

                    ToolBar {
                        padding: 12
                        Layout.fillWidth: true
                        Material.elevation : 0
                        Label {
                            text: qsTr("Network log")
                            Layout.fillWidth: true
                            anchors.bottomMargin: 10
                        }
                    }

                    Flickable {
                        id: flickable
                        flickableDirection: Flickable.VerticalFlick
                        boundsBehavior: Flickable.StopAtBounds
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        TextArea.flickable: TextArea {
                            id: logArea
                            readOnly: true
                        }

                        ScrollBar.vertical: ScrollBar { }

                        Connections {
                            target: app
                            onMessageReceivedQString: logArea.append(Qt.formatDateTime(new Date(), "hh:mm:ss.zzz") + " << " + msg + "\n")
                        }
                        Connections {
                            target: app.network
                            onMessageSentQString: logArea.append(Qt.formatDateTime(new Date(), "hh:mm:ss.zzz") + " >> " + msg)
                        }
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "ConnectedState"
            when: app.connected

            PropertyChanges {
                target: connectedLayoutRoot
                visible: true
            }
            PropertyChanges {
                target: notConnectedLabel
                visible: false
            }
        }
    ]
}
