import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import "qrc:/ui" as UI

Rectangle{

    id: comicDetail

    width: 400
    height: 520

    color: "transparent"
    visible: false

    property bool isDownloadingStatus: false
    property variant comicInfo: {"key": "", "coverUrl": "", "name":"", "site": "", "type": "", "author":"", "updateStatus":""}
    property int startY

    function onDownloadButtonClicked(comicKey, chapters){}
    function getChapterNames(comicKey){}

    function startEnterAnimation(comicInfo, startY)
    {
        comicDetail.comicInfo = comicInfo;
        comicDetail.startY = startY;
        comicDetail.state = "MovingState";
    }

    function startLeaveAnimation()
    {
        comicDetail.state = "StartingState";
    }

    state: "StartingState"

    states:[
        State {
            name: "StartingState"
            PropertyChanges { target: comicDetail; visible: false }
            PropertyChanges { target: chapterControl; visible: false }
            PropertyChanges { target: downloadButton; enabled: false }
        },

        State {
            name: "MovingState"
            PropertyChanges { target: comicDetail; visible: true }
        },

        State {
            name: "ShowingState"
            PropertyChanges { target: comicDetail; visible: true }
            PropertyChanges { target: chapterControl; visible: true }
        }
    ]

    transitions: [
        Transition {
            from: "StartingState"
            to: "MovingState"
            SequentialAnimation{
                PropertyAction { target: comicInfoItem; property:"y"; value:comicDetail.startY; }
                NumberAnimation { target: comicInfoItem; property: "y"; to: 0; duration: 200; easing.type: Easing.OutExpo }
                ScriptAction { script: {chapterControl.prepareChapterModel(); comicDetail.state = "ShowingState"}}
            }
        },

        Transition {
            from: "MovingState"
            to: "ShowingState"
            NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height; duration: 500; easing.type: Easing.OutExpo }
        },

        Transition {
            from: "ShowingState"
            to: "StartingState"
            SequentialAnimation {
                NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height-chapterControl.height; duration: 500; easing.type: Easing.OutExpo }
                PropertyAction { target: chapterControl; property:"visible"; value:false; }
                NumberAnimation { target: comicInfoItem; property: "y"; to: comicDetail.startY; duration: 200; easing.type: Easing.OutExpo }
                PropertyAction { target: comicDetail; property:"visible"; value:false; }
            }
        }
    ]



    UI.ComicInfoItem{
        id: comicInfoItem

        z: 1

        width: parent.width
        height: 120

        comicInfo: comicDetail.comicInfo
        highlight: true

        Button{

            id: downloadButton

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10

            text: "下載"

            onClicked: {
                onDownloadButtonClicked(comicInfo.key, chapterModel.getSelectedChapterNames());
                chapterControl.updateSelectedMessage();
            }
        }
    }

    Rectangle {
        id: chapterControl

        width: parent.width
        height: comicDetail.height - comicInfoItem.height

        y: comicInfoItem.height-chapterControl.height;

        visible: false
        color: "transparent"

        function prepareChapterModel()
        {
            chapterModel.clear();
            var chapterNames = comicDetail.getChapterNames(comicDetail.comicInfo.key);
            for (var i = 0; i < chapterNames.length; i++)
            {
               chapterModel.append({"chapterName": chapterNames[i], "selected": false});
            }
            chapterControl.updateSelectedMessage();
        }

        function updateSelectedMessage()
        {
            var count = chapterModel.getSelectedChapterNames().length;
            selectedMessage.text = "已選擇了 " + count + " 話";
            downloadButton.enabled = !comicDetail.isDownloadingStatus && chapterModel.getSelectedChapterNames().length > 0;
        }

        Rectangle{
            id: selectionControl

            width: parent.width
            height: 40

            z: 1

            color: "#00695c"

            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10

                spacing: 10

                Button{
                    text: "全選"
                    onClicked: {
                        for(var i=0; i < chapterModel.count; i++)
                        {
                            chapterModel.get(i).selected = true;
                        }
                        chapterControl.updateSelectedMessage();
                    }
                }

                Button{
                    text: "取消全選"
                    onClicked: {
                        for(var i=0; i < chapterModel.count; i++)
                        {
                            chapterModel.get(i).selected = false;
                        }
                        chapterControl.updateSelectedMessage();
                    }
                }

                Text {
                    id: selectedMessage

                    anchors.verticalCenter: parent.verticalCenter
                    Layout.fillWidth: parent

                    color:  "#f5f5f5"
                }
            }
        }

        GridView{
            id: chapterGrid

            anchors.top: selectionControl.bottom
            anchors.bottom: parent.bottom

            width: parent.width

            cellWidth: 100
            cellHeight: 40

            model: ListModel {
                id: chapterModel

                function getSelectedChapterNames()
                {
                    var selectedChapterNames = []
                    for(var i=0; i < chapterModel.count; i++)
                    {
                        if(chapterModel.get(i).selected)
                        {
                            selectedChapterNames.push(chapterModel.get(i).chapterName);
                        }
                    }

                    return selectedChapterNames;
                }
            }

            delegate: Rectangle{
                id: chapter

                width: chapterGrid.cellWidth
                height: chapterGrid.cellHeight

                color: model.selected ? "#00bcd4" : "#f5f5f5"

                Text{                   
                    anchors.centerIn: parent
                    font.pointSize: 12
                    text: model.chapterName
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        chapterModel.get(index).selected = !chapterModel.get(index).selected;
                        chapterControl.updateSelectedMessage();
                    }
                }
            }
        }
    }
}
