import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    height: 70
    width: parent.width;

    RowLayout {
        id: itemLayout
        spacing: 10
        anchors.fill: parent

//        Label {
//            id: nameLabel
//            text: name;
//            verticalAlignment: Text.AlignVCenter;
//            horizontalAlignment: Text.AlignLeft
//            visible: !edit;
//            Layout.fillWidth: true
//        }

        TextField {
            id: nameTextField
            text: name
            //visible: edit
            Layout.fillWidth: true
            Binding { target: model; property: "name"; value: nameTextField.text } // Two-way binding
        }

//        Label {
//            id: positionLabel
//            text: position;
//            verticalAlignment: Text.AlignVCenter;
//            horizontalAlignment: Text.AlignLeft
//            visible: !edit;
//            Layout.fillWidth: true
//        }

        TextField {
            id: positionTextField
            text: position
            //visible: edit
            Layout.fillWidth: true
            Binding { target: model; property: "position"; value: positionTextField.text } // Two-way binding
        }
}


    //        Button {
    //            id: goButton
    //            text: qsTr("Go")
    //        }

    //        Button {
    //            contentItem: Image {
    //                fillMode: Image.Pad
    //                horizontalAlignment: Image.AlignHCenter
    //                verticalAlignment: Image.AlignVCenter
    //                source: "qrc:/images/menu.png"
    //            }
    //            onClicked: trackOptionsMenu.open()

    //            Menu {
    //                id: trackOptionsMenu
    //                transformOrigin: Menu.TopLeft

    //                MenuItem {
    //                    text: edit ? qsTr("Done") : qsTr("Edit")
    //                    onTriggered: edit = !edit
    //                }

    //                MenuItem {
    //                    text: qsTr("Delete")

    //                    onTriggered: {
    //                        app.tracksData.deleteTrack(model.modelData);
    //                    }
    //                }
    //            }
    //        }
        }
