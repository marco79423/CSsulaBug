import QtQuick 1.1

Item {
    id: mainView
    width: 500
    height: 600

    Rectangle{
        id: background
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#714f9c"}
            GradientStop { position: 1; color: "#0e0a11"}
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

