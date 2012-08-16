// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    width: 500
    height: 60

    Row {
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: exploreButton
            width: parent.width / 3
            height: parent.height
            color: "#d59c4b"
        }

        Rectangle {
            id: settingButton
            width: parent.width / 3
            height: parent.height
            color: "#43b8e6"
        }

        Rectangle {
            id: aboutButton
            width: parent.width / 3
            height: parent.height
            color: "#888181"
        }
    }
}
