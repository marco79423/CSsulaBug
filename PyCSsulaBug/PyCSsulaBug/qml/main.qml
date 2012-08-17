import QtQuick 1.1

Rectangle {
    id: mainView
    width: 400
    height: 600
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#463260"
        }

        GradientStop {
            position: 0.460
            color: "#5e4382"
        }

        GradientStop {
            position: 1
            color: "#0e0a11"
        }
    }


    Header{
        id: header
        z:1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    ComicList {
        id: comicList
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: footer.top
    }

    Footer {
        id: footer
        z:1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}

