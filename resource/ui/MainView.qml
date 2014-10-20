import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import "qrc:/ui" as UI

ApplicationWindow {

    id: window

    visible:true
    width: 400; height: 600

    minimumWidth: width
    maximumWidth: minimumWidth
    minimumHeight: height
    maximumHeight: minimumHeight

    title: "俗辣蟲漫畫下載器 CSsulaBug"
    color: "darkgray"

    Component.onCompleted: service.update()

    toolBar: ToolBar{
        id: toolbar
        height: 60

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
            onTextChanged: { service.setComicNameFilter(text); }
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
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -20

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
                if(service.isDownloadingStatus) return service.downloadProgress;
                else if(service.isUpdatingStatus) return "正在抓取漫畫資訊，請稍等 ...";
                else return "準備完成，可以選擇要下載的漫畫"
            }
        }
    }

    Rectangle{

        id:page

        anchors.fill: parent

        color: "#004d40"
        state: "MainPageState"

        states:[
            State {
                name: "MainPageState"
                when: !comicDetail.visible
                PropertyChanges { target: searchField ; visible: true; }
                PropertyChanges { target: backButton ; visible: false; }
                PropertyChanges { target: comicList; visible: true; }
            },

            State {
                name: "DetailPageState"
                when: comicDetail.visible
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: true; }
                PropertyChanges { target: comicList; visible: false; }
            }
        ]

        UI.ComicList {
            id: comicList

            anchors.fill: parent

            downloadButtonEnabled: !service.isDownloadingStatus

            model: comicModel
            focus: true

            state: "BusyState"

            function setComicTypeFilter(comicType)
            {
                service.setComicTypeFilter(comicType);
            }

            function onAdvanceButtonClicked(comicInfo, startY)
            {
                comicDetail.startEnterAnimation(comicInfo, startY);
            }

            function onDownloadButtonClicked(comicKey)
            {
                service.download(comicKey);
            }

            Connections {
                target: service
                onUpdateFinishedSignal: if(comicList.state == "BusyState") comicList.state = "DefaultState"
            }
        }

        UI.ComicDetail{
            id: comicDetail
            anchors.fill: parent

            isDownloadingStatus: service.isDownloadingStatus

            function onDownloadButtonClicked(comicKey, chapters)
            {
                service.download(comicKey, chapters);
            }

            function getChapterNames(comicKey)
            {
                return service.getChapterNames(comicKey);
            }
        }
    }
}
