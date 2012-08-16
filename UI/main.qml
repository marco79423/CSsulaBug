import QtQuick 1.1

Item {
    id: mainView
    width: 950
    height: 600

    Rectangle{
        id: background
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#714f9c"}
            GradientStop { position: 1; color: "#0e0a11"}
        }

        LeftSideBar{
            id: leftSideBar
            z:1
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }

        FunctionBar {
            id: header
            z:1
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
        }

        GridView {

            id: comicList
            x: 89
            y: 83
            width: 823
            height: 500
            keyNavigationWraps: false
            flow: GridView.LeftToRight
            boundsBehavior: Flickable.DragAndOvershootBounds
            anchors.rightMargin: 38
            anchors.bottomMargin: 17
            cellWidth: 410
            cellHeight: 140
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: leftSideBar.right
            anchors.margins: 25

            delegate: Comic {
                cover: model.cover
                name: model.name
                site: model.site
                type: model.type
                author: model.author
                lastUpdated: model.lastUpdated
            }

            model: ComicModel{}
        }
    }
}

