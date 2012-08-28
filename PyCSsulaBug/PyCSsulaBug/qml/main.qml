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
        anchors {
            top : parent.top
            left: parent.left
            right: parent.right
        }
    }

    ComicList {
        id: comicList
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
        }
    }

    Footer {
        id: footer
        z:1

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}

