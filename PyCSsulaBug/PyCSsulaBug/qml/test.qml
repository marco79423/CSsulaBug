import QtQuick 1.1

Rectangle{

    width: 200; height: 250
    color: "lightblue"
    ListView {
        anchors.fill: parent

        delegate: Text { text: "Comic: " + name + ", " + type }
        model: comicModel
    }

    MouseArea {

        anchors.fill:  parent
        onClicked: {
            console.log("update")
            core.update()
        }
    }
}
