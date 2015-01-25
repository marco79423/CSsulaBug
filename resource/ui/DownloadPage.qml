import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import "qrc:/ui/globals.js" as Globals

Rectangle {
    id: downloadPage
    width: 400 //暫定
    height: 540 //暫定

    color: Globals.MainColor2

    ListView {
        anchors.fill: parent
        model: downloadComicModel

        delegate: Rectangle {
            id: downloadComic
            property bool isCurrent: index == 0;

            width: parent.width
            height: isCurrent ? 90 : 60

            color: isCurrent ? Globals.MainColor3 : Globals.SoftWhite

            Image {
                id: downloadComicImage
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter

                width: downloadComic.isCurrent ? 56 : 40
                height: downloadComic.isCurrent ? 70 : 50
                source: model.coverUrl
            }

            ColumnLayout{

                anchors.top: downloadComicImage.top
                anchors.bottom: downloadComicImage.bottom
                anchors.left: downloadComicImage.left
                anchors.leftMargin: 90
                anchors.right: parent.right

                RowLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Flickable {
                        id: downloadComicNameFlick
                        width: 250
                        height: downloadComicName.height
                        contentWidth: downloadComicName.width
                        clip: true

                        TextEdit {
                            id: downloadComicName

                            font.family: "標楷體"
                            font.pixelSize: 25
                            font.bold: true
                            horizontalAlignment: Text.AlignLeft

                            text: model.name

                            readOnly: true
                            selectByMouse: true
                        }


                        SequentialAnimation{
                            running: downloadComicImage.width > downloadComicNameFlick.width
                            loops: Animation.Infinite
                            NumberAnimation { target: downloadComicNameFlick; property: "contentX"; to: downloadComicName.width - downloadComicNameFlick.width; duration: 3000}
                            PauseAnimation { duration: 500 }
                            NumberAnimation { target: downloadComicNameFlick; property: "contentX"; to: 0; duration: 3000}
                            PauseAnimation { duration: 500 }
                        }
                    }

                    Button {
                        text: "刪除"
                        onClicked: service.cancelDownload(model.key);
                        style: ButtonStyle {
                            background: Rectangle {
                                implicitWidth: 30
                                implicitHeight: 25
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "#888"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                                }
                            }
                        }
                    }
                }

                ProgressBar {
                    visible: downloadComic.isCurrent
                    value: service.downloadProgress.ratio
                    style: ProgressBarStyle {
                        background: Rectangle {
                            color: Globals.SoftWhite
                            implicitWidth: 290
                            implicitHeight: 15
                        }

                        progress: Rectangle {
                            color: Globals.ProgressBarColor
                        }
                    }

                    Text {
                       anchors.right: parent.right
                       text: Math.round(service.downloadProgress.ratio * 100) + "%"
                    }
                }
                TextEdit {
                    visible: downloadComic.isCurrent
                    readOnly: true; selectByMouse: true;  text: service.downloadProgress.message
                }
            }
        }
   }
}

