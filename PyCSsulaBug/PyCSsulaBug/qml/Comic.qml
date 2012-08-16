import QtQuick 1.1

Rectangle {
    id: comicInfo
    width: 380
    height: 120
    color: "#9e9595"
    radius: 10
    border.width: 3
    border.color: "#ffffff"

    property string cover
    property string name
    property string site
    property string type
    property string author
    property string lastUpdated

    Image {
        id:comicCover
        source: cover
        height: comicInfo.height - 20
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
