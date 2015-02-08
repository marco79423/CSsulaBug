import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import "qrc:/ui" as UI
import "qrc:/ui/globals.js" as Globals

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

    Component.onCompleted: service.collectComicInfos()

    toolBar: ToolBar{
        id: toolbar
        height: 60

        style: ToolBarStyle{
            background: Rectangle{
                color: Globals.MainColor1
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
                    color: Globals.SoftWhite
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

        /*Button{

            id: settingPageButton

            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            text: "設定"
            onClicked: {
                console.log("setting");
            }
        }*/


        Button{

            id: downloadPageButton

            anchors.right: parent.right//settingPageButton.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            checkable: true
            text: "我的下載"
        }
    }

    statusBar: StatusBar{
        Text {
            text: {
                if(service.downloadStatus){
                    return "[進度 " + Math.round(service.downloadProgress.ratio * 100) + "% ] " + service.downloadProgress.message;
                }else if(service.collectingStatus) return "正在抓取漫畫資訊，請稍等 ...";
                else return "準備完成，可以選擇要下載的漫畫"
            }
        }
    }

    Rectangle{

        id:page

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: parent.width * 2
        height: parent.height

        color: Globals.MainColor1
        state: "MainPageState"

        Behavior on x {
            NumberAnimation { duration: 500; easing.type: Easing.InOutQuad }
        }

        states:[
            State {
                name: "MainPageState"
                when: !comicDetail.visible && !downloadPageButton.checked
                PropertyChanges { target: page; x: 0 }
                PropertyChanges { target: searchField ; visible: true; }
                PropertyChanges { target: backButton ; visible: false; }
                PropertyChanges { target: comicList; visible: true; }
            },

            State {
                name: "DetailPageState"
                when: comicDetail.visible && !downloadPageButton.checked
                PropertyChanges { target: page; x: 0 }
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: true; }
                PropertyChanges { target: comicList; visible: false; }
            },

            State {
                name: "DownloadPageState"
                when: downloadPageButton.checked
                PropertyChanges { target: page ; x: -page.width / 2 }
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: false; }
            }
        ]

        UI.ComicList {
            id: comicList

            width: parent.width / 2
            height: parent.height

            focus: true

            state: "BusyState"

            function onAdvanceButtonClicked(comicInfo, startY)
            {
                comicDetail.startEnterAnimation(comicInfo, startY);
            }

            Connections {
                target: service
                onCollectingFinishedSignal: if(comicList.state == "BusyState") comicList.state = "DefaultState"
            }
        }

        UI.ComicDetail{
            id: comicDetail
            width: comicList.width
            height: comicList.height
        }

        UI.DownloadPage {
            id:　downloadPage

            width: page.width / 2
            height: page.height
            x: page.width / 2
        }
    }
}
