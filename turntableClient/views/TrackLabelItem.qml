import QtQuick 2.0

Rectangle{
    id: trackLabel

    property double imgAngle: 0
    property string trackText


    Text {
        id: trackLabelText
        text: trackText //qsTr("Voie Test")
        font.bold: true
        font.pixelSize: 10
        anchors.horizontalCenter: trackLabel.horizontalCenter
        anchors.verticalCenter: trackLabel.verticalCenter
    }
    height: trackLabelText.paintedHeight
    width: trackLabelText.paintedWidth
    color: "white"

    anchors.centerIn: parent

    property int posX: trackLabel.width/2
    property int posY: trackLabel.height/2
//    posX: trackLabel.width/2
//    posY: trackLabel.height/2


    //    text:  "Voie Test" // trackText
    transform: [
        Rotation {
            angle : -1 * imgAngle
            origin.x: trackLabel.width/2
            origin.y: trackLabel.height/2
        }
        , Translate {
            x: parent.width/2* 1.05
            y: -2
        }
        , Rotation {
            origin.x: trackLabel.width/2
            origin.y: trackLabel.height/2
            angle: imgAngle
        }

    ]

}

