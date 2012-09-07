// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {

    Component.onCompleted: core.update()

    id: mainView
    width: 400 ; height: 600

    Rectangle {
        color: "#6c48a6"
        anchors.fill: parent

    }
    ExplorePanel {

    }
    Menu {
        anchors.bottom: parent.bottom
    }
}
