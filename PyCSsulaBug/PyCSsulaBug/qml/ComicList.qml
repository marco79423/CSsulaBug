// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ListView {

    id: comicList
    height: parent.height
    width: parent.width

    keyNavigationWraps: false
    boundsBehavior: Flickable.DragAndOvershootBounds


    highlight:  Component {
        Rectangle {
            width: 400
            height: 120
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
