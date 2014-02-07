import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ApplicationWindow {

    visible:true
    width: 400; height: 600
    title: "CSsulaBug 漫畫下載器"
    color: "darkgray"

    Component.onCompleted: core.update()

    toolBar: ToolBar {
        RowLayout{
            width: parent.width
            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "點此搜尋想下載的漫畫 ..."
                onTextChanged: { core.setFilter(text); }
            }

            Button{
                text: "下載"
                onClicked: {
                    var key = core.getKey(comicList.currentIndex);
                    core.download(key, ".")
                }
            }
        }
    }

    statusBar: StatusBar{
        Text {
            text: comicList.state == "updating" ? "正在抓取漫畫資訊，請稍等 ..." : "準備完成，可以選擇要下載的漫畫";
        }
    }

    /*Image {

        anchors.centerIn: parent
        width: 350

        source: "images/lazchi.png"
        fillMode: Image.PreserveAspectFit
    }*/

    ListView {
        id: comicList
        anchors.fill: parent
        model: comicModel
        focus: true

        delegate: comic
        highlight: highlight

        highlightFollowsCurrentItem: false

        state: "updating"
        states: [
            State {
                name: "updating"
                PropertyChanges { target: loading ; opacity: 0.9; }
            },

            State {
                name: "updateCompleted"
                PropertyChanges { target: loading ; opacity: 0}
                PropertyChanges { target: comicList ; focus: true}
            }
        ]

        AnimatedImage {
            id: loading
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 60
            height: 60
            source: "images/loading.gif"
        }

        Connections {
            target: core
            onUpdateFinish: comicList.state = "updateCompleted"
        }
    }

    Component {
        id: comic

        Item {
            width: 400
            height: 120

            Rectangle {
                anchors.centerIn: parent
                width: 390
                height: 115
                color: "white"
                opacity: 0.9

                RowLayout{
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    Image { source: model.coverUrl }
                    ColumnLayout{
                        Text { text: name ; font.pointSize: 20; font.bold: true; horizontalAlignment: Text.AlignLeft }
                        Text { text: "漫畫來源：" + site }
                        Text { text: "漫畫類型：" + type }
                        Text { text: "作者：" + author}
                        Text { text: "最新更新：" + lastUpdated}
                    }
                }
            }
        }
    }

    Component {
        id: highlight
        Item {
            width: 400
            height: 120
            y: comicList.currentItem.y

            Rectangle {
                anchors.centerIn: parent
                width: 390
                height: 115
                color: "#0000BB"
            }
        }
    }
}
