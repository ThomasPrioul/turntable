import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
//import QtQuick.Controls.Universal 2.0
import "views/pages"
import "views/dialogs"

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480
    title: qsTr("PFE HMI prototype", "windowTitle")

    header: ToolBar {
        id: header
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

//            Label {
//                id: titleLabel
//                text: qsTr("Proto PFE")
//                font.pixelSize: 20
//                elide: Label.ElideRight
//                horizontalAlignment: Qt.AlignHCenter
//                verticalAlignment: Qt.AlignVCenter
//                Layout.fillWidth: true
//            }

            TabBar {
                id: tabBar
                Layout.fillWidth: true
                currentIndex: centerPane.currentIndex
                background: Rectangle {
                    color: Material.primary
                }

                Material.foreground: "#FFE0E0E0"
                Material.accent: "white"

                Repeater {
                    model: ListModel {
                       ListElement { title: qsTr("Turn table", "pagename") }
//                       ListElement { title: qsTr("Train control", "pagename") }
                       ListElement { title: qsTr("Depot", "pagename") }
//                       ListElement { title: qsTr("Scripts", "pagename") }
                   }
                    TabButton {
                        text: model.title
                    }
                }
            }

            ToolButton {
                id: trainButton
                text: "Trains"
                onClicked: trainsDialog.open()
            }

            ToolButton {
                id: scriptButton
                text: "Scripts"
                onClicked: scriptDialog.open()
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/img/menu.png"
                }

                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: qsTr("Connection")
                        onTriggered: connectDialog.open()
                    }

                    MenuItem {
                        text: "Calibration"
                        onTriggered: calibrationDialog.open()
                    }

                    MenuItem { text: qsTr("About")
                        onTriggered: aboutDialog.open()
                    }

                    MenuItem {
                        text: qsTr("Exit")
                        onTriggered: Qt.quit();
                    }
                }
            }
        }
    }

    StackLayout {
        id: centerPane
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        TurnTable {
            id: turnTablePage
        }

//        TrainControlPage {
//            id: trainControlPage
//        }

        TrainDepotPage {
            id: trainDepotPage
        }

//        ScriptPage {
//            id: scriptPage
//        }
    }

    ConnectDialog {
        id: connectDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2 - header.height
        width: 400
        height: 200
    }

    Popup {
        id: calibrationDialog

        x: (window.width - width) / 2
        y: (window.height - height) / 2 - header.height

        modal: true
        focus: true
        margins:50

        contentHeight: window.height
        contentWidth: window.width

        Label {
            text: "Calibration"
            font.bold: true
        }

        Item {

        }

    }

    Popup {
        id: trainsDialog
        x: window.width - width - trainButton.width
        y : 0
        modal: true
        focus: true
        contentHeight: 200
        contentWidth: 300

        Item {

        }
    }

    Popup {
        id: scriptDialog
        x: window.width - width
        y : 0
        modal: true
        focus: true
        contentHeight: 200
        contentWidth: 300

        ScriptPage {
            id:layout
        }
    }

    AboutDialog {
        id: aboutDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2 - header.height
        contentWidth: 400
    }
}
