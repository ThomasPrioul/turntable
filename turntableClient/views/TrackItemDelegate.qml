import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0

Item {
    id: root
    //width: parent.width;
    signal editClicked(string name, int position, bool relay);
    RowLayout {
        id: itemLayout
        spacing: 10
        anchors.fill: parent

        Button{
            id: nameButton
            text: name
            //scale: 0.5
            onClicked: app.turntable.moveToTrack(model.modelData)
        }
/*
        Label {
            id: nameLabel
            text: name;
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
        }
*/
        Label {
            id: positionLabel
            text: position;
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
        }
        /*CheckBox{
            id: relayLabel
            //checkState: relay;
            Layout.fillWidth: true
        }*/



        ToolButton {
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: Material.Theme === Material.LightTheme ? "qrc:/images/menu.png" : "qrc:/images/+material/menu.png"
            }
            onClicked: trackOptionsMenu.open()

            Menu {
                id: trackOptionsMenu
                transformOrigin: Menu.TopLeft

                MenuItem {
                    text: qsTr("Goto")
                    enabled: !app.turntable.busy && (app.turntable.nbSteps > -1) && (app.turntable.position !== position)
                    onTriggered: app.turntable.moveToTrack(model.modelData)
                }

                MenuItem {
                    text: qsTr("Edit")
                    enabled: !app.turntable.busy
                    onTriggered: root.editClicked(name, position, relay);
                }

                MenuItem {
                    text: qsTr("Delete")
                    enabled: !app.turntable.busy
                    onTriggered: app.turntable.removeServiceTrack(name)
                }
            }
        }
    }

    states: [
        State {
            name: "OnTrackState"
            when: (app.turntable.position === position)

//            PropertyChanges {
//                target: nameLabel
//                color: "#0F0FFF"
//            }

            PropertyChanges {
                target: positionLabel
                color: "#0F0FFF"
            }
        }
    ]
}
