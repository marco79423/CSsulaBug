import QtQuick 1.1

ListView {
    //width: 100; height: 100
    delegate: Rectangle {
        height: 100
        width: 100
        Text {
            text: modelData
        }
    }
    model: comicModel
}
/*
ListView {
     width: 100; height: 100
     anchors.fill: parent

     model: myModel
     delegate: Rectangle {
         height: 25
         width: 100
         Text { text: modelData }
     }
 }
*/
