import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "qrc:/ui/globals.js" as Globals

Rectangle {
    id: comicInfoItem

    width: 400
    height: 120

    property variant comicInfo
    property bool highlight: false

    color: highlight ? Globals.MainColor3: Globals.SoftWhite

    Image {
        id: coverImage

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        width: 80
        height: 100
        source: comicInfo.coverUrl
    }

    ColumnLayout{
        anchors.top: coverImage.top
        anchors.bottom: coverImage.bottom
        anchors.left: coverImage.right
        anchors.leftMargin: 20

        spacing: 3

        Flickable {
            id: nameFlick
            width: 290
            height: 30
            contentWidth: nameText.width
            clip: true

            TextEdit {
                id: nameText
                text: comicInfo.name
                font.family: "標楷體"
                font.pixelSize: 25
                font.bold: true
                horizontalAlignment: Text.AlignLeft

                readOnly: true
                selectByMouse: true
            }

            SequentialAnimation{
                running: nameText.width > nameFlick.width
                loops: Animation.Infinite
                NumberAnimation { target: nameFlick; property: "contentX"; to: nameText.width - nameFlick.width; duration: 3000}
                PauseAnimation { duration: 500 }
                NumberAnimation { target: nameFlick; property: "contentX"; to: 0; duration: 3000}
                PauseAnimation { duration: 500 }
            }
        }

        TextEdit { readOnly: true; selectByMouse: true; text: "漫畫來源：" + comicInfo.site }
        TextEdit { readOnly: true; selectByMouse: true;  text: "漫畫類型：" + comicInfo.type }
        TextEdit { readOnly: true; selectByMouse: true;  text: "作者：" + comicInfo.author; visible: comicInfo.author !== "" }
        TextEdit { readOnly: true; selectByMouse: true;  text: "更新狀態：" + comicInfo.updateStatus}
    }

}

