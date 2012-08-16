// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

GridView {

    id: comicList
    height: 480

    keyNavigationWraps: false
    flow: GridView.LeftToRight
    boundsBehavior: Flickable.DragAndOvershootBounds
    cellWidth: 410
    cellHeight: 140

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
