import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Popup {
    id: popup
    modal: true
    focus: true
    property int margin: 10

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: margin
        spacing: 5

        Label {
            text: qsTr("Connect to DCC server")
            font.bold: true
        }

        TextField {
            placeholderText: qsTr("ipaddress:port")
            Layout.fillWidth: true
            Layout.preferredWidth: 300
        }

        Button {
            id:okButton
            text: qsTr("OK")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredWidth: 120
            Layout.bottomMargin: 10
            onClicked: popup.close()
        }
    }
}
