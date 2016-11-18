import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ColumnLayout {
    id: mainLayout


//    ColumnLayout {
//        id: mainLayout
//        anchors.fill: parent
//        anchors.margins: margin
//        spacing: 5

    Label {
        id: titleLabel
        text: qsTr("Scripts")
        font.bold: true
    }

    ListView {
        Layout.preferredHeight: 100
        Layout.preferredWidth: 200
        model: ListModel {
           ListElement { title: "Script 1" }
           ListElement { title: "Script 2" }
           ListElement { title: "Script 3" }
           ListElement { title: "Script 4" }
           ListElement { title: "Script 5" }
       }

        anchors.fill: parent

        delegate: ItemDelegate {
            width: parent.width
            text: model.title
        }
    }
}
