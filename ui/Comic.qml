import QtQuick 1.1

Rectangle {

    id: comic

    property string coverUrl
    property string key
    property string name
    property string site
    property string type
    property string author
    property string lastUpdated

    width: 400
    height: 130
    color: "#958b8b"
    border { width: 2 ; color: "#ffffff" }

    Image {
        id:comicCover
        source: coverUrl
        width: height * 0.8
        height: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.margins: 10
    }


    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: comicCover.right
        anchors.leftMargin: 10
        Text { text: name ; font.pointSize: 20; font.bold: true; font.family: "微軟正黑體";horizontalAlignment: Text.AlignLeft }
        Text { text: "漫畫來源：" + site ;font.family: "微軟正黑體" }
        Text { text: "漫畫類型：" + type ;font.family: "微軟正黑體" }
        Text { text: "作者：" + author ;font.family: "微軟正黑體" }
        Text { text: "最新更新：" + lastUpdated ;font.family: "微軟正黑體" }
    }

}
