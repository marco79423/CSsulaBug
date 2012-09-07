// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: explorePanel
    width: 400
    height: 540

    FunctionPanel {
        id: functionPanel
    }

    ListView {

        id: comicList

        anchors.top: functionPanel.bottom
        width: 400
        height: 480

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
