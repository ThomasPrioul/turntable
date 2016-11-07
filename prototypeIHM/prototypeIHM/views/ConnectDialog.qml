import QtQuick 2.6
import QtQuick.Controls 2.0

Popup {
    modal: true
    focus: true

    contentHeight: connectColumn.height

    Column {
        id: connectColumn
        spacing: 20

        Label {
            text: qsTr("Connect to server")
            font.bold: true
        }

        Label {
            width: aboutDialog.availableWidth
            text: "PFE - pont tournant pour modélisme ferroviaire\nMade with Qt Quick Controls 2."
            wrapMode: Label.Wrap
            font.pixelSize: 12
        }

        Label {
            width: aboutDialog.availableWidth
            text: "Thomas Prioul\nPolytech' Tours DII - 2016/2017"
            font.bold: true
            font.pixelSize: 12
        }
    }
}
