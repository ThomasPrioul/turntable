import QtQuick 2.6
import QtQuick.Controls 2.0

Popup {
    id: baseDialog
    modal: true
    focus: true

    contentHeight: aboutColumn.height

    Column {
        id: aboutColumn
        spacing: 20

        Label {
            text: qsTr("About")
            font.bold: true
        }

        Label {
            width: baseDialog.availableWidth
            text: "PFE - pont tournant pour modélisme ferroviaire.\nMade with Qt Quick Controls 2."
            wrapMode: Label.Wrap
            font.pixelSize: 12
        }

        Label {
            width: baseDialog.availableWidth
            text: "Thomas Prioul\nPolytech' Tours DII - 2016/2017"
            font.bold: true
            font.pixelSize: 12
        }
    }
}
