import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "qrc:/ui" as UI

Rectangle{

    id: comicList

    width: 400
    height: 520
    color:  "transparent"

    property variant model
    property bool downloadButtonEnabled: true

    function onAdvanceButtonClicked(comicInfo, startY){}
    function onDownloadButtonClicked(comicInfo){}

    state: "DefaultState"

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

    ListView {

        id: comicListView

        anchors.fill: parent
        currentIndex: 0
        boundsBehavior: Flickable.DragOverBounds

        model: comicList.model

        AnimatedImage {
            id: loadingImage
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 60
            height: 60
            source: "images/loading.gif"
        }

        delegate: UI.ComicInfoItem{

            width: comicList.width

            comicInfo: model
            highlight: ListView.isCurrentItem

            MouseArea {
                visible: comicListView.currentIndex != index;
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
                        comicList.onAdvanceButtonClicked(comicInfo, comicListView.currentItem.y);
                    }
                }

                Button{
                    enabled: comicList.downloadButtonEnabled

                    text: "下載"
                    onClicked: {
                        comicListView.currentIndex = index;
                        comicList.onDownloadButtonClicked(comicInfo.key);
                    }
                }
            }
        }
    }
}
