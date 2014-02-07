import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ApplicationWindow {

    visible:true
    width: 400; height: 600
    title: "CSsulaBug 漫畫下載器"

    Component.onCompleted: core.update()

    toolBar: ToolBar {
        RowLayout{
            width: parent.width
            TextField {
                id: searchField
                Layout.fillWidth: true
            }

            Button{
                text: "下載"
                onClicked: {
                    var key = comicModel.getKey(comicList.currentIndex);
                    core.download(key, ".")
                }
            }
        }
    }

    statusBar: StatusBar{
        Text { text: comicList.state }
    }

    ListView {
        id: comicList
        anchors.fill: parent
        model: comicModel
        focus: true
        delegate: comic
        highlight: highlight
        state: "updating"

        states: [
            State {
                name: "updating"
                PropertyChanges { target: loading ; opacity: 1}
            },

            State {
                name: "updateCompleted"
                PropertyChanges { target: loading ; opacity: 0}
                PropertyChanges { target: comicList ; focus: true}
            }
        ]

        AnimatedImage {
            id: loading
            anchors.centerIn: parent
            scale: 0.2
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
        Rectangle {
            width: comic.width
            height: comic.height
            color: "darkgray"
            //z: 10
            y: comicList.currentItem.y
        }
    }


}

/*
Item {

    Component.onCompleted: core.update()

    id: mainView
    width: 400 ; height: 600

    Rectangle {
        id: background
        color: "#6c48a6"
        anchors.fill: parent

    }

    ContentView {
        id: contentView

        Behavior on x {
            NumberAnimation { duration: 100 }
        }
    }


}
*/
