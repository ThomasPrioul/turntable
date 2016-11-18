import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

GridLayout {
    anchors.centerIn: parent
    property real _width: 200

    Item {

        Rectangle {
            id: turnTableCircle
            width: _width
            height: _width
            color: "white"
            border.color: "black"
            border.width: 1
            radius: width * 0.5
        }

        Rectangle {
            width: _width
            height: _width/4
            anchors.centerIn: turnTableCircle
            color: "transparent"
            border.color: "black"
            border.width: 1
        }
    }
}

