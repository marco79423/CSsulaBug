import QtQuick 1.1

Rectangle{

    width: childrenRect.width
    height: childrenRect.height

    Component {
        id: highlight
        Rectangle {
            width: parent.width; height: 10
            color: "lightsteelblue"; radius: 5
            y: list.currentItem.y

        }
    }

    ListView {
        id: list
        width: 180; height: 200
        model: 10
        delegate: Text { text: index }

        highlight: highlight
        highlightFollowsCurrentItem: false
        focus: true
    }
}
