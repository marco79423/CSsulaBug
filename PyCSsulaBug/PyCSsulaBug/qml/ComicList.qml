// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ListView {

    id: comicList
    height: parent.height
    width: parent.width

    keyNavigationWraps: false
    boundsBehavior: Flickable.DragAndOvershootBounds

    delegate: Comic {
        cover: model.cover
        name: model.name
        site: model.site
        type: model.type
        author: model.author
        lastUpdated: model.lastUpdated
    }

    model: comicModel
}
