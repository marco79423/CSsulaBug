// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 64
    height: 600
    color: "#383244"
    border.color: "#a6a0a0"

    Column{
        anchors.fill: parent
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: exploreButton
            width: parent.width
            height: 101
            color: "#d59c4b"
        }

        Rectangle {
            id: settingButton
            width: parent.width
            height: 101
            color: "#43b8e6"
        }

        Rectangle {
            id: aboutButton
            width: parent.width
            height: 101
            color: "#888181"
        }
    }
}
