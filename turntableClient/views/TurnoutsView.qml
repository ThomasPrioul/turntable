import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import turntable.client.models 1.0

Item {
    id: turnoutsViewRoot
    anchors.fill: parent
    width: 800
    height: 432

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        rowSpacing: 10
        columnSpacing: 10

        Pane {
            enabled: !app.turntable.busy
            Layout.fillHeight: true
            Layout.fillWidth: true
            Material.elevation: 6
            padding: 0
            id: panelTurnouts
            x: 0

            Rectangle{
                id: rectangle
                x: 0
                y: 0
                width: 780
                height: 412
                color: "#006633"
            }

            Label{
                text: app.turnouts.sizeLabel
                id: label
            }

            Button{
                x: 679
                y: 372
                width: 101
                height: 40
                text: "Button"
            }

            Button {
                x: 463
                y: 358
                text: "Button"
            }

            Button {
                x: 319
                y: 341
                text: "Taille"
                z: 1
                onClicked: {
                    app.turnouts.sizeScreen(turnoutsViewRoot.height, turnoutsViewRoot.width);
                }
            }

            Image {
                id: image900
                x: 30
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        app.turnouts.cmdTrackTrace(900);
                    }
                }

                Text {
                    id: text10
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("A")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image916
                x: 30
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text11
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("Q")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image925
                x: 240
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text12
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("Z")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image902
                x: 270
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text13
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("C")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image903
                x: 300
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text14
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("D")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image904
                x: 330
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text15
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("E")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image917
                x: 420
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text16
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("R")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image913
                x: 510
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text17
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("N")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image909
                x: 540
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text18
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("J")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image908
                x: 570
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text19
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("I")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image76
                x: 330
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image918
                x: 270
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text20
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("S")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image905
                x: 420
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text9
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("F")
                    font.bold: true
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Image {
                id: image922
                x: 120
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text8
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("W")
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15
                }
            }

            Image {
                id: image923
                x: 300
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos1/8100.ico"

                Text {
                    id: text21
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    text: qsTr("X")
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Image {
                id: image0
                x: 660
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1040.ico"
            }

            Image {
                id: image1
                x: 600
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1040.ico"
            }

            Image {
                id: image2
                x: 540
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1040.ico"
            }

            Image {
                id: image3
                x: 480
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1034.ico"
            }

            Image {
                id: image4
                x: 270
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1034.ico"
            }

            Image {
                id: image5
                x: 240
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/1032.ico"
            }

            Image {
                id: image6
                x: 210
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/1032.ico"
            }

            Image {
                id: image7
                x: 240
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/1032.ico"
            }

            Image {
                id: image8
                x: 150
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/1034.ico"
            }

            Image {
                id: image9
                x: 60
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/1034.ico"
            }

            Image {
                id: image12
                x: 690
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image13
                x: 630
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image14
                x: 570
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image15
                x: 510
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image16
                x: 450
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image18
                x: 390
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image19
                x: 270
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image20
                x: 300
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image21
                x: 300
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image22
                x: 330
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image23
                x: 330
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image24
                x: 390
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image25
                x: 450
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image26
                x: 450
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image27
                x: 360
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image28
                x: 330
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image29
                x: 390
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image30
                x: 480
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image31
                x: 390
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image32
                x: 480
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image33
                x: 510
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image34
                x: 510
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image35
                x: 480
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image36
                x: 450
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image37
                x: 360
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image38
                x: 360
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image39
                x: 540
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image42
                x: 660
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image43
                x: 630
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image44
                x: 600
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image45
                x: 570
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image46
                x: 600
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image47
                x: 540
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0003.ico"
            }

            Image {
                id: image48
                x: 180
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image49
                x: 600
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0005.ico"
            }

            Image {
                id: image50
                x: 570
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0005.ico"
            }

            Image {
                id: image51
                x: 630
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/0005.ico"
            }

            Image {
                id: image52
                x: 450
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image53
                x: 180
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image54
                x: 210
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image55
                x: 60
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image56
                x: 90
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image57
                x: 120
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image59
                x: 0
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0008.ico"
            }

            Image {
                id: image60
                x: 0
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0008.ico"
            }

            Image {
                id: image61
                x: 720
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0050.ico"
            }

            Image {
                id: image62
                x: 750
                y: 90
                width: 30
                height: 30
                source: "../Icones/Pos0/0052.ico"
            }

            Image {
                id: image63
                x: 150
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image64
                x: 210
                y: 180
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image65
                x: 300
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }


            Image {
                id: image78
                x: 240
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image79
                x: 450
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image80
                x: 480
                y: 120
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image81
                x: 390
                y: 150
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image85
                x: 120
                y: 180
                width: 30
                height: 30
                source: "../Icones/Pos0/0004.ico"
            }

            Image {
                id: image86
                x: 180
                y: 180
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image88
                x: 210
                y: 60
                width: 30
                height: 30
                source: "../Icones/Pos0/1043.ico"
            }

            Image {
                id: image89
                x: 240
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0006.ico"
            }

            Image {
                id: image90
                x: 270
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image91
                x: 270
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0000.ico"
            }

            Image {
                id: image92
                x: 210
                y: 30
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Image {
                id: image93
                x: 240
                y: 0
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Text {
                id: text1
                x: 360
                y: 150
                width: 30
                height: 30
                color: "#ff6820"
                text: "10"
                font.bold: true
                textFormat: Text.AutoText
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text2
                x: 360
                y: 90
                width: 30
                height: 30
                color: "#ff6820"
                text: "11"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text3
                x: 420
                y: 60
                width: 30
                height: 30
                color: "#ff6820"
                text: "12"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text4
                x: 420
                y: 30
                width: 30
                height: 30
                color: "#ff6820"
                text: "13"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text5
                x: 420
                y: 0
                width: 30
                height: 30
                color: "#ff6820"
                text: "14"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text6
                x: 30
                y: 180
                width: 30
                height: 30
                color: "#ff6820"
                text: "15"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text7
                x: 30
                y: 90
                width: 30
                height: 30
                color: "#ff6820"
                text: "16"
                font.bold: true
                wrapMode: Text.NoWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Image {
                id: image87
                x: 90
                y: 180
                width: 30
                height: 30
                source: "../Icones/Pos0/0001.ico"
            }

            Text {
                id: text22
                x: 60
                y: 210
                width: 90
                height: 30
                color: "#ffffff"
                text: "Sortie"
                textFormat: Text.AutoText
                wrapMode: Text.NoWrap
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: text23
                x: 150
                y: 210
                width: 90
                height: 30
                color: "#ffffff"
                text: "Entrée"
                wrapMode: Text.NoWrap
                textFormat: Text.AutoText
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: text24
                x: 90
                y: 240
                width: 120
                height: 30
                color: "#ffffff"
                text: "Rotonde"
                wrapMode: Text.NoWrap
                textFormat: Text.AutoText
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: text25
                x: 690
                y: 120
                width: 90
                height: 30
                color: "#ffffff"
                text: "Vers la gare"
                wrapMode: Text.NoWrap
                textFormat: Text.AutoText
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: text26
                x: 390
                y: 210
                width: 210
                height: 60
                color: "#ffffff"
                text: "Le dépot"
                wrapMode: Text.NoWrap
                textFormat: Text.AutoText
                font.pixelSize: 40
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

}
