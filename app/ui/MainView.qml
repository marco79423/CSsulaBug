import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ApplicationWindow {

    visible:true
    width: 400; height: 600
    maximumWidth: width; minimumWidth: width
    minimumHeight: 600

    title: "CSsulaBug 漫畫下載器"
    color: "darkgray"

    //Component.onCompleted: comicInfoService.update()

    toolBar: ToolBar {
        id: toolBar
        enabled: false
        RowLayout{
            width: parent.width
            TextField {
                Layout.fillWidth: true
                placeholderText: "點此搜尋想下載的漫畫至桌面 ..."
                onTextChanged: { comicInfoService.setFilter(text); }
            }

            Button{
                id: downloadButton
                text: "下載"
                onClicked: {
                    comicList.state = "downloading";
                    var key = comicInfoService.getKey(comicList.currentIndex);
                    downloadService.download(key);
                }
            }
        }
    }

    statusBar: StatusBar{
        Text {
            text: {
                if(comicList.state == "updating")
                    return "正在抓取漫畫資訊，請稍等 ...";
                else if(comicList.state == "ready")
                    return "準備完成，可以選擇要下載的漫畫";
                else
                    return downloadService.downloadProgress
            }
        }
    }

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
                PropertyChanges { target: loadingImage ; opacity: 0.9; }
                PropertyChanges { target: comicList ; enabled: false}
                PropertyChanges { target: toolBar ; enabled: false}
            },

            State {
                name: "ready"
                PropertyChanges { target: loadingImage ; opacity: 0}
                PropertyChanges { target: comicList ; enabled: true; focus: true}
                PropertyChanges { target: toolBar ; enabled: true}
            },

            State {
                name: "downloading"
                PropertyChanges { target: loadingImage ; opacity: 0.9;}
                PropertyChanges { target: comicList ; enabled: false; focus: false}
                PropertyChanges { target: toolBar ; enabled: false}
            }
        ]

        AnimatedImage {
            id: loadingImage
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 60
            height: 60
            source: "images/loading.gif"
        }

        Connections {
            target: comicInfoService
            onUpdateFinish: if(comicList.state == "updating") comicList.state = "ready"
        }

        Connections {
            target: downloadService
            onDownloadFinish: comicList.state = "ready"
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
                    Image { source: coverUrl }
                    ColumnLayout{
                        Text { text: name ; font.pointSize: 20; font.bold: true; horizontalAlignment: Text.AlignLeft }
                        Text { text: "漫畫來源：" + site }
                        Text { text: "漫畫類型：" + type }
                        Text { text: "作者：" + author}
                        Text { text: "最新更新：" + lastUpdated}
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    comicList.currentIndex = index
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
