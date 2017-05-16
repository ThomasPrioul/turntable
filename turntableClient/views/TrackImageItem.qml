import QtQuick 2.0

Image {
    id: trackImage
    property double imgAngle: 0
    property bool occupied: false
    property QtObject model
    signal trackSelected(QtObject track);

    anchors.centerIn: parent
    antialiasing: true
    fillMode: Image.PreserveAspectFit
    height: parent.height / (170/55)
    source: occupied ? "qrc:/images/TrackGreen.png" : "qrc:/images/TrackGrey.png"

    MouseArea {
        id : clickArea
        width: parent.width
        height: parent.height
        onClicked: trackImage.trackSelected(model);
    }

    transform: [
        Translate {
            x: parent.width/2 + trackImage.width/2
            y: -2
        }
        , Rotation {
            origin.x: trackImage.width/2
            origin.y: trackImage.height/2
            angle: imgAngle
        }
    ]
}
