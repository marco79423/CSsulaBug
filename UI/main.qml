import QtQuick 1.1

Rectangle {
    id: mainView
    width: 910
    height: 600
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#714f9c"
        }

        GradientStop {
            position: 1
            color: "#0e0a11"
        }
    }


    Row{
        id: topRow
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: leftSideBar.right
        anchors.leftMargin: 10
        spacing: 10
        Rectangle {
            id: inputArea
            width: 283
            height: 33
            color: "#979696"
            radius: 10

            TextInput {
                id: textInput
                text: "搜尋漫畫"
                font.family: "微軟正黑體"
                anchors.bottomMargin: 0
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.fill: parent
                clip: false
                cursorVisible: true
                font.strikeout: false
                autoScroll: false
                font.pixelSize: 21
            }
        }

        Rectangle {
            id: downloadButton
            width: 80
            height: 33
            color: "#823a8d"
            radius: 8
            border.width: 2
            border.color: "#beb8b8"

            Text {
                id: downloadText
                text: "下載"
                font.family: "微軟正黑體"
                verticalAlignment: Text.AlignVCenter
                font.bold: false
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 21
            }

            MouseArea {
                id: downloadMouseArea
                hoverEnabled: true
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: leftSideBar
        width: 64
        color: "#383244"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 0
        border.color: "#a6a0a0"

        Rectangle {
            id: exploreButton
            x: 11
            y: 17
            width: 43
            height: 101
            color: "#d59c4b"
            radius: 10
        }

        Rectangle {
            id: settingButton
            x: 11
            y: 131
            width: 43
            height: 101
            color: "#43b8e6"
            radius: 10
        }

            Rectangle {
                id: aboutButton
                x: 11
                y: 379
                width: 43
                height: 101
                color: "#888181"
                radius: 10
            }
    }

    GridView {

        id: comicList
        x: 74
        y: 52

        cellWidth: 410
        cellHeight: 130
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: leftSideBar.right
        anchors.top: topRow.bottom
        anchors.margins: 10
        snapMode: SnapToRow

        delegate: Comic {
            cover: model.cover
            name: model.name
            site: model.site
            type: model.type
            author: model.author
            lastUpdated: model.lastUpdated
        }
        model: ListModel {
            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/bleach.jpg"
                name: "死神"
                site: "SF"
                type: "熱血類"
                author: "久保帶人"
                lastUpdated: "500英文[未完成]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/Naruto.jpg"
                name: "火影忍者"
                site: "SF"
                type: "熱血類"
                author: "岸本齊使"
                lastUpdated: "593话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/OnePiece.jpg"
                name: "海贼王/One Piece"
                site: "SF"
                type: "熱血類"
                author: "尾田荣一郎"
                lastUpdated: "674话[未完结]"
            }

            ListElement {
                cover: "http://comic.sfacg.com/Logo/e6ec812f-7007-4375-98b2-70e1325e7f87.jpg"
                name: "红Kure-Nai"
                site: "SF"
                type: "社會類"
                author: "片山宪太朗"
                lastUpdated: "051话[未完结] "
            }
        }
    }
}
