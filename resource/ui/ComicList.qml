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

    function setComicTypeFilter(comicType){}

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

    ListView{

        id: comicTypeListView
        z:1
        width: parent.width
        height: 30
        model: ListModel {
            id: comicTypeModel

        }

        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds

        delegate: Rectangle{
            width: 60
            height: comicTypeListView.height
            color: ListView.isCurrentItem ? "#004d40" : "#00695c"

            Text {
                anchors.centerIn: parent
                text: model.comicType
                color: "#f5f5f5"
                font.pixelSize: 15
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    comicTypeListView.currentIndex = index;
                    var comicType = (model.comicType === "全部")? "" : model.comicType;
                    comicList.setComicTypeFilter(comicType);
                }
            }
        }

        Component.onCompleted: prepareComicTypeFilter()

        function prepareComicTypeFilter()
        {
            var comicTypes = ["全部", "耽美", "熱血", "校園", "推理", "機戰", "冒險", "運動", "搞笑", "科幻", "魔幻","恐怖" ,"社會" ,"愛情","武俠"];
            for (var i = 0; i < comicTypes.length; i++)
            {
               comicTypeModel.append({"comicType": comicTypes[i]});
            }
        }
    }

    ListView {

        id: comicListView

        anchors.top: comicTypeListView.bottom
        width: parent.width
        height: 490

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
