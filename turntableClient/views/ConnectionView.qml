import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0

ColumnLayout {
    id : root
    anchors.fill: parent
    transformOrigin: Item.Top
    spacing: 10
    signal connectClicked(string ip, int port);
    property TextField ipInput : ipTextInput
    property TextField portInput : portTextInput

    Label {
        text : qsTr("Connect to DCC server")
        font.pixelSize: 16
    }

    ColumnLayout {
        spacing: 0
        Layout.fillWidth: true

        Label {
            text : qsTr("IP")
            Layout.fillWidth: true
        }

        TextField {
            id: ipTextInput
            Layout.fillWidth: true
            placeholderText: "127.0.0.1"
            validator: RegExpValidator {
                regExp: /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
            }
        }

    }

    ColumnLayout {
        spacing: 0

        Label {
            text : qsTr("Port")
            Layout.fillWidth: true
        }

        TextField {
            id: portTextInput
            Layout.fillWidth: true
            placeholderText: "2017"
            validator: IntValidator {
                bottom:1024
                top: 65535
            }
        }
    }

    Button {
        id: connectionButton
        text: qsTr("Connect")
        Layout.alignment: Qt.AlignRight
        enabled: ipTextInput.acceptableInput && portTextInput.acceptableInput
        onClicked: root.connectClicked(ipTextInput.text, portTextInput.text)
    }
}

