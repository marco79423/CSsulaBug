// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 64
    color: "#383244"
    border.color: "#a6a0a0"

    Column{

        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 15

        Rectangle {
            id: exploreButton
            width: 43
            height: 101
            color: "#d59c4b"
            radius: 10
        }

        Rectangle {
            id: settingButton
            width: 43
            height: 101
            color: "#43b8e6"
            radius: 10
        }

        Rectangle {
            id: aboutButton
            width: 43
            height: 101
            color: "#888181"
            radius: 10
        }
    }
}
