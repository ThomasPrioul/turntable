import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import "views"

ApplicationWindow {
    id: window
    height: 480
    width: 800
    visible: true

    function getHeight() {
        return window.height - window.header.implicitHeight;
    }

    Component.onCompleted: {
        window.title = app.applicationDisplayName;
    }

    header: ToolBar {
        id: header
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            TabBar {
                id: bar
                background: Rectangle {
                    color: Material.primary
                }
                Material.foreground: "#FFE0E0E0"
                Material.accent: "white"
                Layout.fillWidth: true

                TabButton {
                    text: qsTr("Home")
                }
                TabButton {
                    text: qsTr("Turntable")
                }
                TabButton {
                    text: qsTr("Locomotives")
                }
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: app.connected ? qsTr("Disconnect") : qsTr("Connect")
                        onTriggered: {
                            if (app.connected)
                                app.network.disconnectFromHost();
                            else {
                                connectionPopup.open();
                                connectionView.ipInput.forceActiveFocus();
                            }
                        }
                    }

                    MenuItem {
                        text :qsTr("About")
                        enabled: false
                    }

                    MenuItem {
                        text: qsTr("Exit")
                        onTriggered: {
                            app.network.disconnectFromHost();
                            Qt.quit();
                        }
                    }
                }
            }
        }
    }

    StackLayout {
        currentIndex: bar.currentIndex
        anchors.fill: parent

        HomeView {
            id: homeView
        }

        TurntableView {
            id: turntableView
            enabled: app.connected
        }

        LocomotivesView {
            id: locomotivesView
        }
    }

    Popup {
        id: connectionPopup
        x: Math.max(0, window.width/2 - connectionPopup.implicitWidth)
        y: Math.max(0, window.getHeight()/2 - connectionPopup.implicitHeight/2)
        width: 2*implicitWidth
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        ConnectionView {
            id: connectionView
            anchors.fill: parent
            onConnectClicked: {
                app.network.connectToHost(ip, port);
            }
            onVisibleChanged: {
                if (connectionView.visible) {
                    connectionView.ipInput.text = app.settings.serverIP;
                    connectionView.portInput.text = app.settings.serverPort;
                }
                else if (app.connected) {
                    app.settings.serverIP = connectionView.ipInput.text;
                    app.settings.serverPort = parseInt(connectionView.portInput.text);
                    app.settings.save();
                }
            }
        }

        Connections {
            target: app
            onConnectedChanged: {
                if (app.connected && connectionPopup.visible)
                    connectionPopup.close();
            }
        }
    }
}
