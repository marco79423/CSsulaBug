// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {

    Component.onCompleted: core.update()

    id: mainView
    width: 400 ; height: 600

    Rectangle {
        id: background
        color: "#6c48a6"
        anchors.fill: parent

    }

    ContentView {
        id: contentView

        Behavior on x {
            NumberAnimation { duration: 100 }
        }
    }

    Rectangle {
        id: menu

        anchors.bottom: parent.bottom
        width: 400
        height: 60

        color: "#331a69"

        Row {
            anchors.centerIn: parent

            Button {
                text: "瀏覽漫畫"
                onClicked: contentView.x = 0
            }

            Button {
                text: "我的下載"
                onClicked: contentView.x = - (contentView.width / 3)
            }

            Button {
                text: "關於軟體"
                onClicked: contentView.x = - 2 * (contentView.width / 3)
            }
        }
    }
}
