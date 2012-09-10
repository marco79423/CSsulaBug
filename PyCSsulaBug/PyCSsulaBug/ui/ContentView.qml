// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {

    id: contentView

    width: 1200
    height: 540

    Row {
        anchors.fill: parent

        Item {
            id: exploreView
            width: parent.width / 3
            height: parent.height

            Rectangle {
                id: functionPanel
                width: 400
                height: 60

                color: "#331a69"

                Button {
                    id: downloadButton
                    anchors { right: parent.right ; rightMargin: 10 ; verticalCenter: parent.verticalCenter}
                    text: "下載"

                    onClicked: {
                        var key = comicList.currentItem.key;
                        core.download(key, ".")
                    }
                }
            }

            ListView {

                id: comicList

                anchors.top: functionPanel.bottom
                width: parent.width
                height: parent.height - functionPanel.height

                boundsBehavior: Flickable.DragAndOvershootBounds
                clip: true

                highlight:  Component {
                    Rectangle {
                        width: 400
                        height: 130
                        color: "white"
                        radius: 5
                        z: 10
                        opacity: 0.5
                        y: comicList.currentItem.y
                    }
                }

                delegate: Comic {
                    cover: model.cover
                    key: model.key
                    name: model.name
                    site: model.site
                    type: model.type
                    author: model.author
                    lastUpdated: model.lastUpdated
                }

                model: comicModel
                highlightFollowsCurrentItem: false
                focus: true
            }
        }

        Item {
            id: downloadView
            width: parent.width / 3
            height: parent.height

            Connections {
                target: core
                onDownloadInfo: console.log(core.progress())
            }
        }

        Item {
            id: aboutView
            width: parent.width / 3
            height: parent.height

            Image {

                id: lazchi
                anchors.centerIn: parent
                width: 350

                source: "images/lazchi.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {

                anchors { top: lazchi.bottom ; topMargin: 20 }
                anchors { right: parent.right ; rightMargin: 20 }
                text: "類死雞工作室"
                font { pointSize: 24}
            }
        }
    }
}
