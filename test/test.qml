import QtQuick 1.1

Rectangle {
  width: 200
  height: 200
  Text {
    x: 66
    y: SequentialAnimation { // new animation
      running: true
      repeat: true
      NumberAnimation { to: 150; easing: "easeOutBounce"; duration: 2000 }
      PauseAnimation { duration: 1000 }
      NumberAnimation { to: 50; easing: "easeOutQuad"; duration: 1000 }
    }
    text: "Hello World"
  }
}
