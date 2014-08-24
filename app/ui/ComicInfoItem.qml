import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Rectangle {

    width: 400
    height: 120

    property variant comicInfo
    property bool highlight: false

    color: highlight ? "#009688": "#f5f5f5"

    RowLayout{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        spacing: 20

        Image { source: comicInfo.coverUrl}
        ColumnLayout{
            Text { text: comicInfo.name ; font.pointSize: 20; font.bold: true; horizontalAlignment: Text.AlignLeft }
            Text { text: "漫畫來源：" + comicInfo.site }
            Text { text: "漫畫類型：" + comicInfo.type }
            Text { text: "作者：" + comicInfo.author}
            Text { text: "最新更新：" + comicInfo.lastUpdated}
        }
    }
}

