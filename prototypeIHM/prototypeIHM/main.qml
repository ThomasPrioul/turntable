import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import "views"

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480
    title: qsTr("PFE HMI prototype", "windowTitle")

//    Settings {
//        id: settings
//        property string style: "Material"
//    }

    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

//            ToolButton {
//                contentItem: Image {
//                    fillMode: Image.Pad
//                    horizontalAlignment: Image.AlignHCenter
//                    verticalAlignment: Image.AlignVCenter
//                    source: "qrc:/img/drawer.png"
//                }
//                onClicked: drawer.open()
//            }

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
                       ListElement { title: qsTr("Train control", "pagename") }
                       ListElement { title: qsTr("Depot", "pagename") }
                       ListElement { title: qsTr("Scripts", "pagename") }
                   }
                    TabButton {
                        text: model.title
                    }
                }
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
                        text: qsTr("Settings")
                        enabled: false
                        //onTriggered: settingsPopup.open()
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

    SwipeView {
        id: centerPane
        anchors.fill: parent
        currentIndex: tabBar.currentIndex


        TurnTablePage {
            id: turnTablePage
        }

        TrainControlPage {
            id: trainControlPage
        }

        TrainDepotPage {
            id: trainDepotPage
        }

        ScriptPage {
            id: scriptPage
        }
    }

//    StackView {
//        id: stackView
//        anchors.fill: parent

//        initialItem: Pane {
//            id: pane

//            Item {
//                anchors.fill: parent
//                RowLayout {
//                    anchors.centerIn: parent

//                    Button {
//                        id: button1
//                        text: qsTr("Settings")
//                        enabled: false
//                        //onClicked: settingsPopup.open()
//                    }

//                    Button {
//                        id: button2
//                        text: qsTr("Open drawer")
//                        onClicked: drawer.open()
//                    }
//                }
//            }
//        }
//    }

//    Drawer {
//        id: drawer
//        width: Math.min(window.width, window.height) / 3 * 2
//        height: window.height

//        ListView {
//            id: listView
//            currentIndex: -1
//            anchors.fill: parent

//            delegate: ItemDelegate {
//                width: parent.width
//                text: model.title
//                highlighted: ListView.isCurrentItem
//                onClicked: {
//                    if (listView.currentIndex != index) {
//                        listView.currentIndex = index
//                        //titleLabel.text = model.title
//                        stackView.replace(model.source)
//                    }
//                    drawer.close()
//                }
//            }

//            model: ListModel {
//                ListElement { title: "BusyIndicator"; source: "qrc:/views/BusyIndicatorPage.qml" }
//            }

//            ScrollIndicator.vertical: ScrollIndicator { }
//        }
//    }

//    Popup {
//        id: settingsPopup
//        x: (window.width - width) / 2
//        y: window.height / 6
//        width: Math.min(window.width, window.height) / 3 * 2
//        height: settingsColumn.implicitHeight + topPadding + bottomPadding
//        modal: true
//        focus: true

//        contentItem: ColumnLayout {
//            id: settingsColumn
//            spacing: 20

//            Label {
//                text: qsTr("Settings")
//                font.bold: true
//            }

//            RowLayout {
//                spacing: 10

//                Label {
//                    text: qsTr("Style:")
//                }

//                ComboBox {
//                    id: styleBox
//                    property int styleIndex: -1
//                    model: ["Default", "Material", "Universal"]
//                    Component.onCompleted: {
//                        styleIndex = find(settings.style, Qt.MatchFixedString)
//                        if (styleIndex !== -1)
//                            currentIndex = styleIndex
//                    }
//                    Layout.fillWidth: true
//                }
//            }

//            Label {
//                text: qsTr("Restart required")
//                color: "#e41e25"
//                opacity: styleBox.currentIndex !== styleBox.styleIndex ? 1.0 : 0.0
//                horizontalAlignment: Label.AlignHCenter
//                verticalAlignment: Label.AlignVCenter
//                Layout.fillWidth: true
//                Layout.fillHeight: true
//            }

//            RowLayout {
//                spacing: 10

//                Button {
//                    id: okButton
//                    text: qsTr("Ok")
//                    onClicked: {
//                        settings.style = styleBox.displayText;
//                        appHelpers.syncSettings();
//                        settingsPopup.close();
//                    }

//                    //Material.foreground: Material.primary
//                    //Material.background: "transparent"
//                    //Material.elevation: 0

//                    Layout.preferredWidth: 0
//                    Layout.fillWidth: true
//                }

//                Button {
//                    id: cancelButton
//                    text: qsTr("Cancel")
//                    onClicked: {
//                        styleBox.currentIndex = styleBox.styleIndex
//                        settingsPopup.close()
//                    }

//                    //Material.background: "transparent"
//                    //Material.elevation: 0

//                    Layout.preferredWidth: 0
//                    Layout.fillWidth: true
//                }
//            }
//        }
//    }

    AboutDialog {
        id: aboutDialog
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
    }
}
