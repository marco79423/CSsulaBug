import QtQuick 1.1

ListView {
     width: 200; height: 250
     anchors.fill: parent

     model: comicModel
     delegate: Text { text: "Comic: " + Name + ", " + Type }
}

/*
ListView {
     width: 200; height: 250
     anchors.fill: parent

     model: myModel
     delegate: Text { text: "Animal: " + type + ", " + size }
}*/
