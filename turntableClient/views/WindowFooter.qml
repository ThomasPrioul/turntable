import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4

Rectangle {
    id: footerBackground

    RowLayout {
        anchors.margins: 10
        anchors.fill: parent
        spacing: 10

        StatusIndicator {
            id: connectionStateIndicator
            color: "#35e02f"
            Layout.maximumHeight: 32
            Layout.maximumWidth: 32
            on: app.connected
        }
        Text {
            id: connectionStateText
            text: app.connected ? qsTr("Connected") : qsTr("Disconnected")
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
        }
        Button {
            id: connectButton
            text: app.connected ? qsTr("Disconnect") : qsTr("Connect")
            onClicked: connectionPopup.open()
            //            onClicked: {
            //                if (!app.connected) {
            //                    app.network.connectToHost("127.0.0.1", 2017);
            //                }
            //                else {
            //                    app.network.disconnectFromHost();
            //                }
            //            }
        }
    }
}
