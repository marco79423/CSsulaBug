// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{

    width: 500
    height: 60
    color: "#383244"

    Rectangle {
        id: inputArea
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        width: 300
        height:parent.height * 0.8
        color: "#979696"

        TextInput {
            id: textInput
            x: 5
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.leftMargin: 5

            text: "搜尋漫畫"
            font.family: "微軟正黑體"
            font.pixelSize: 21
            font.strikeout: false

            clip: false
            cursorVisible: true
            autoScroll: false
        }
    }

    Rectangle {
        id: downloadButton
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: 80
        height:parent.height
        color: "#823a8d"

        Text {
            id: downloadText
            color: "#000000"
            text: "下載"
            font.family: "微軟正黑體"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: false
            anchors.fill: parent
            font.pixelSize: 21
            //color: downloadMouseArea.pressed ? "#bc7fc6": "#823a8d"
        }

        MouseArea {
            id: downloadMouseArea
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {}
        }


    }
}


