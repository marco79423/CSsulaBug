// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: functionPanel
    width: 400
    height: 60

    Rectangle {
        anchors.fill: parent
        color: "#331a69"
    }

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
