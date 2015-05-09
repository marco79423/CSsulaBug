import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2

import "qrc:/ui/globals.js" as Globals

Rectangle {
    id: settingsPage
    width: 400
    height: 540

    color: Globals.MainColor2

    Rectangle {

        anchors.centerIn: parent
        width: parent.width - 30
        height: parent.height - 30

        color: Globals.MainColor3

        GridLayout {

            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
            }

            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Label {text: "下載路徑："}
            TextField {
                id: downloadPathTextField
                Layout.fillWidth: true
                readOnly: true
                text: service.downloadPath

                MouseArea{
                    anchors.fill: parent
                    onClicked: fileDialog.open()
                }
            }
        }

        FileDialog {
            id: fileDialog
            title: "選擇要下載的漫畫路徑"
            selectFolder: true
            onAccepted: {
                if(fileDialog.fileUrl){
                    service.downloadPath = fileDialog.fileUrl.toString().replace("file:///", "");
                }
            }
        }
    }
}

