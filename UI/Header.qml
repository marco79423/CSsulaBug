// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    width: 425
    height: 60
    color: "#383244"
    border.color: "#a6a0a0"
    radius: 5

    Rectangle {
        id: inputArea
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        height:30
        width: 300
        color: "#979696"
        radius: 5

        TextInput {
            id: textInput
            x: 5
            width: 295
            height: 30
            text: "搜尋漫畫"
            font.family: "微軟正黑體"
            font.pixelSize: 21
            font.strikeout: false

            anchors.topMargin: 2
            anchors.leftMargin: 5
            anchors.fill: parent

            clip: false
            cursorVisible: true
            autoScroll: false
        }
    }

    Rectangle {
        id: downloadButton
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: inputArea.right
        anchors.leftMargin: 20
        width: 80
        height: 35
        color: "#823a8d"
        radius: 10

        border.width: 2
        border.color: "#beb8b8"

        Text {
            id: downloadText
            text: "下載"
            font.family: "微軟正黑體"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: false
            anchors.fill: parent
            font.pixelSize: 21
        }

        MouseArea {
            id: downloadMouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered : { downloadButton.color = "#bc7fc6" }
            onExited: { downloadButton.color = "#823a8d" }
            }


        }
}


