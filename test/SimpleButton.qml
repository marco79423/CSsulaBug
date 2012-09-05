// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
     id: button
     //...

     property color buttonColor: "lightblue"
     property color onHoverColor: "gold"
     property color borderColor: "white"

     signal buttonClick()
     onButtonClick: {
         console.log(buttonLabel.text + " clicked" )
     }

     MouseArea{
         id: buttonMouseArea
         onClicked: buttonClick()
         hoverEnabled: true
         onEntered: parent.border.color = onHoverColor
         onExited:  parent.border.color = borderColor
     }

     //determines the color of the button by using the conditional operator
     color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
 }
