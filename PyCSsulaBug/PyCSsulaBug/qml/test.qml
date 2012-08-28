import QtQuick 1.1

Rectangle{

    ListView {
         width: 200; height: 250
         anchors.fill: parent

         model: comicModel
         delegate: Text { text: "Comic: " + Name + ", " + Name }
    }

}



