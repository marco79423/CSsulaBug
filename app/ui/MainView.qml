import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import "qrc:/ui" as UI

ApplicationWindow {

    id: window

    visible:true
    width: 400; height: 600
    maximumWidth: width
    minimumHeight: height

    title: "俗辣蟲漫畫下載器 CSsulaBug"
    color: "darkgray"

    Component.onCompleted: service.update()

    toolBar: ToolBar{
        id: toolbar
        height: 60

        enabled: !service.downloading

        style: ToolBarStyle{
            background: Rectangle{
                color: "#004d40"
            }
        }

        TextField {
            id: searchField

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            width: 200

            style: TextFieldStyle {
                background: Rectangle{
                    color: "#f5f5f5"
                }
            }

            placeholderText: "點此搜尋想下載的漫畫至桌面 ..."
            onTextChanged: { service.setFilter(text); }
        }

        Button{
            id: backButton

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            text: "返回"
            onClicked: {comicDetail.startLeaveAnimation(); }
        }

        Button{

            id: settingButton

            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -25

            width: 50
            height: 50

            style: ButtonStyle{
                background: Rectangle{

                    color: "#ffeb3b"
                    radius: 100
                }
            }

            /*text: "設定"
            onClicked: {
                console.log("setting");
            }*/
        }
    }

    statusBar: StatusBar{
        Text {
            text: {
                if(service.downloading) return service.downloadProgress;
                else if(service.updating) return "正在抓取漫畫資訊，請稍等 ...";
                else return "準備完成，可以選擇要下載的漫畫"
            }
        }
    }

    Rectangle{

        id:page

        anchors.fill: parent

        enabled: !service.downloading

        color: "transparent"
        state: "MainPageState"

        states:[
            State {
                name: "MainPageState"
                when: !comicDetail.visible
                PropertyChanges { target: searchField ; visible: true; }
                PropertyChanges { target: backButton ; visible: false; }
                PropertyChanges { target: comicListView; visible: true; }
            },

            State {
                name: "DetailPageState"
                when: comicDetail.visible
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: true; }
                PropertyChanges { target: comicListView; visible: false; }
            }
        ]

        UI.ComicListView {
            id: comicListView

            anchors.fill: parent

            model: comicModel
            focus: true

            state: "BusyState"

            function onAdvanceButtonClicked(comicInfo)
            {
                comicDetail.startEnterAnimation(comicInfo, comicListView.currentItem.y);
            }

            function onDownloadButtonClicked(comicKey)
            {
                service.download(comicKey);
            }

            Connections {
                target: service
                onUpdateFinishedSignal: if(comicListView.state == "BusyState") comicListView.state = "DefaultState"
            }
        }

        UI.ComicDetail{
            id: comicDetail
            anchors.fill: parent

            function onDownloadButtonClicked(comicKey, chapters)
            {
                service.download(comicKey, chapters);
            }
        }
    }
}
