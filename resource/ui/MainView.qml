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

    Rectangle {
        id: tabs
        z: 1

        width: parent.width
        height: 35

        color: Globals.MainColor1

        Rectangle {

            enabled: false;

            id: mainPageButton

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10

            width: 70
            height: 30
            color: enabled ? Globals.MainColor1: Globals.MainColor2

            Text {
                anchors.centerIn: parent
                text: "漫畫清單"
                color: Globals.SoftWhite
                font.pointSize: 11
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainPageButton.enabled = false;
                    downloadPageButton.enabled = true;
                    settingsPageButton.enabled = true;
                }
            }
        }

        Rectangle {

            id: downloadPageButton

            anchors.bottom: parent.bottom
            anchors.left: mainPageButton.right

            width: 70
            height: 30
            color: enabled ? Globals.MainColor1: Globals.MainColor2

            Text {
                anchors.centerIn: parent
                text: "我的下載"
                color: Globals.SoftWhite
                font.pointSize: 11
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainPageButton.enabled = true;
                    downloadPageButton.enabled = false;
                    settingsPageButton.enabled = true;
                }
            }
        }

        Rectangle {

            id: settingsPageButton

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 10

            width: 70
            height: 30
            color: enabled ? Globals.MainColor1: Globals.MainColor2

            Text {
                anchors.centerIn: parent
                text: "設定"
                color: Globals.SoftWhite
                font.pointSize: 11
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainPageButton.enabled = true;
                    downloadPageButton.enabled = true;
                    settingsPageButton.enabled = false;
                }
            }
        }
    }

    Rectangle{
        id: page
        anchors.top: tabs.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        state: "MainPageState"

        states:[
            State {
                name: "MainPageState"
                when: !mainPageButton.enabled
                PropertyChanges { target: mainPage ; visible: true; }
                PropertyChanges { target: settingsPage; visible: false; }
                PropertyChanges { target: downloadPage; visible: false }
            },

            State {
                name: "DownloadPageState"
                when: !downloadPageButton.enabled
                PropertyChanges { target: mainPage ; visible: false; }
                PropertyChanges { target: settingsPage; visible: false; }
                PropertyChanges { target: downloadPage; visible: true; }
            },

            State {
                name: "SettingsPageState"
                when: !settingsPageButton.enabled
                PropertyChanges { target: mainPage ; visible: false; }
                PropertyChanges { target: settingsPage; visible: true; }
                PropertyChanges { target: downloadPage; visible: false; }
            }
        ]


        Rectangle{

            id: mainPage

            anchors.fill: parent

            color: Globals.MainColor2

            state: "listMode"
            states:[
                State {
                    name: "listMode"
                    when: !comicDetail.visible
                    PropertyChanges { target: searchField ; visible: true; }
                    PropertyChanges { target: backButton ; visible: false; }
                    PropertyChanges { target: comicList; visible: true; }
                },

                State {
                    name: "detailMode"
                    when: comicDetail.visible
                    PropertyChanges { target: searchField ; visible: false; }
                    PropertyChanges { target: backButton ; visible: true; }
                    PropertyChanges { target: comicList; visible: false; }
                }
            ]

            Rectangle {
                id: searchPanel

                z: 1

                anchors.top: tabs.bottom
                width: parent.width
                height: 50

                color: Globals.MainColor2

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

                    placeholderText: "點此搜尋想下載的漫畫 ..."
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
            }

            UI.ComicList {
                id: comicList

                anchors {
                    top: searchPanel.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

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

                anchors {
                    top: searchPanel.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
            }
        }

        UI.DownloadPage {
            id:　downloadPage
            anchors.fill: parent

            visible: false
        }

        UI.SettingsPage {
            id: settingsPage
            anchors.fill: parent

            visible: false
        }
    }
}
