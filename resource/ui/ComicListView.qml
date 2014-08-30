﻿import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "qrc:/ui" as UI

ListView {

    id: comicListView

    width: 400
    height: 520

    currentIndex: 0
    boundsBehavior: Flickable.DragOverBounds

    state: "DefaultState"

    function onAdvanceButtonClicked(comicInfo){}
    function onDownloadButtonClicked(comicInfo){}

    states: [

        State {
            name: "DefaultState"
            PropertyChanges { target: loadingImage ; opacity: 0}
        },

        State {
            name: "BusyState"
            PropertyChanges { target: loadingImage ; opacity: 0.9; }
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

    delegate: UI.ComicInfoItem{

        width: comicListView.width

        comicInfo: model
        highlight: ListView.isCurrentItem

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                comicListView.currentIndex = index
            }
        }

        ColumnLayout{

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10
            spacing: 5

            Button{
                text: "進階"
                onClicked: {
                    comicListView.currentIndex = index;
                    comicListView.onAdvanceButtonClicked(comicInfo);
                }
            }

            Button{
                text: "下載"
                onClicked: {
                    comicListView.currentIndex = index;
                    comicListView.onDownloadButtonClicked(comicInfo.key);
                }
            }
        }
    }
}