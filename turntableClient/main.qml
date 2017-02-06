import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import "views"

ApplicationWindow {
    id: window
    height: 480
    visible: true
    width: 800
    //Material.theme: Material.Dark
    Material.primary: Material.Green
    Material.accent: Material.LightGreen

    Component.onCompleted: {
        window.title = app.applicationDisplayName;
    }

    ColumnLayout {
        anchors.fill: parent

        ToolBar {
            Layout.fillWidth: true

            RowLayout {
                spacing: 20
                anchors.fill: parent

                ToolButton {
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        source: "images/drawer.png"
                    }
                    //                    onClicked: {
                    //                        if (stackView.depth > 1) {
                    //                            stackView.pop()
                    //                            listView.currentIndex = -1
                    //                        } else {
                    //                            drawer.open()
                    //                        }
                    //                    }
                }

                Label {
                    id: titleLabel
                    text: window.title
                    font.pixelSize: 20
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }

                ToolButton {
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        source: "images/menu.png"
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
                                else
                                    connectionPopup.open();
                            }
                        }
                        MenuItem {
                            text: qsTr("Exit")
                            onTriggered: Qt.quit()
                        }
                    }
                }
            }
        }

        Rectangle {
            color: Material.background
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Popup {
            id: connectionPopup
            x: Math.max(0, window.width/2 - connectionPopup.implicitWidth)
            y: Math.max(0, window.height/2 - connectionPopup.implicitHeight/2)
            width: 2*implicitWidth
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            ConnectionView {
                id: connectionView
                anchors.fill: parent
                onConnectClicked: app.network.connectToHost(ip, port)
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
}
