// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{

    width: 400
    height: 60

    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#847a7a"
        }

        GradientStop {
            position: 0.070
            color: "#693f71"
        }

        GradientStop {
            position: 1
            color: "#383244"
        }
    }

    Rectangle {
        id: inputArea
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        width: 200
        height:parent.height * 0.6
        color: "#979696"
        radius: 10
        border.width: 0
        border.color: "#823a8d"
        opacity: 0.9

        TextInput {
            id: textInput
            x: 5
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.leftMargin: 5

            text: "搜尋漫畫"
            opacity: 1
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
        anchors.rightMargin: 20
        width: 80
        height:parent.height * 0.6
        radius: 10
        border.width: 1
        border.color: "#5a5959"
        //color: "#823a8d"

        gradient: Gradient {
            GradientStop { position: 0; color: "#714f9c"}
            GradientStop { position: 0.5; color: "#383244"}
            GradientStop { position: 1; color: "#714f9c"}
        }

        Text {
            id: downloadText
            color: "#b5b5b5"
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
            onClicked: {}
        }


    }
}


