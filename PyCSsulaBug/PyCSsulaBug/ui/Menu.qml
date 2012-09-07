// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {

    id: menu
    width: 400
    height: 60

    Rectangle {
        color: "#331a69"
        anchors.fill: parent
    }

    Row {
        anchors.centerIn: parent

        Button {
            text: "瀏覽漫畫"
        }

        Button {
            text: "我的下載"
        }

        Button {
            text: "關於軟體"
        }
    }
}
