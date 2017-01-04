import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {

            Connections {
                  target: network
                  onMessageReceived: console.log("Received : " + message.toString());
              }

            RowLayout {
                TextInput {
                    id: hostnameTextInput
                    text: "192.168.32.1"
                }
                TextInput {
                    id: portTextInput
                    text: "2002"
                }

                Button {
                    text: qsTr("connect")
                    onClicked: network.connectToHost(hostnameTextInput.text, portTextInput.text)
                }

                Button {
                    text: qsTr("disconnect")
                    onClicked: network.disconnectFromHost()
                }
            }
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
