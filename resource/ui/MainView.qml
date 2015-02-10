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
        height: 80

        style: ToolBarStyle{
            background: Rectangle{
                color: Globals.MainColor1

                Rectangle {
                    anchors.bottom: parent.bottom

                    width: parent.width
                    height: 50 - 3

                    color: Globals.MainColor2
                }
            }
        }

        TextField {
            id: searchField

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 5

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

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 5

            text: "返回"
            onClicked: {comicDetail.startLeaveAnimation(); }
        }


        Button{

            enabled: false;

            id: mainPageButton

            anchors.right: downloadPageButton.left
            anchors.top: parent.top
            anchors.rightMargin: 5

            text: "漫畫清單"

            onClicked: {
                mainPageButton.enabled = false;
                downloadPageButton.enabled = true;
            }

            style: ButtonStyle {
                label: Text {
                    y: 5
                    text: control.text
                    color: Globals.SoftWhite
                    font.pointSize: 15
                }
                background: Rectangle {
                    implicitWidth: 70
                    implicitHeight: 30
                    color: control.enabled ? Globals.MainColor1: Globals.MainColor2
                }
            }
        }

        Button{

            id: downloadPageButton

            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top

            text: "我的下載"

            onClicked: {
                mainPageButton.enabled = true;
                downloadPageButton.enabled = false;
            }

            style: ButtonStyle {
                label: Text {
                    y: 5
                    text: control.text
                    color: Globals.SoftWhite
                    font.pointSize: 15
                }
                background: Rectangle {
                    implicitWidth: 60
                    implicitHeight: 30
                    color: control.enabled ? Globals.MainColor1: Globals.MainColor2
                }
            }
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
        id: page
        anchors.fill: parent

        state: "MainPageState"

        states:[
            State {
                name: "MainPageState"
                when: !comicDetail.visible && downloadPageButton.enabled
                PropertyChanges { target: downloadPage; visible: false }
                PropertyChanges { target: searchField ; visible: true; }
                PropertyChanges { target: backButton ; visible: false; }
                PropertyChanges { target: comicList; visible: true; }
            },

            State {
                name: "DetailPageState"
                when: comicDetail.visible && downloadPageButton.enabled
                PropertyChanges { target: downloadPage; visible: false }
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: true; }
                PropertyChanges { target: comicList; visible: false; }
            },

            State {
                name: "DownloadPageState"
                when: !downloadPageButton.enabled
                PropertyChanges { target: downloadPage; visible: true; }
                PropertyChanges { target: searchField ; visible: false; }
                PropertyChanges { target: backButton ; visible: false; }
            }
        ]


        Rectangle{

            id: mainPage

            anchors.fill: parent

            color: Globals.MainColor2

            UI.ComicList {
                id: comicList

                width: parent.width
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
        }

        UI.DownloadPage {
            id:　downloadPage
            anchors.fill: parent

            visible: false
        }
    }
}
