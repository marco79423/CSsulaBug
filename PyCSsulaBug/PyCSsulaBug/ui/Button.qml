// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: container

    property string text
    property bool disabled: false
    signal clicked

    width: childrenRect.width
    height: childrenRect.height

    Image {
        id: image
        source: parent.state == "" ? "images/button.png" : "images/button_press.png"
    }

    MouseArea {
        anchors.fill: image
        onClicked: {
            if (!container.disabled)
                container.clicked()
        }
        onPressed: {
            if (!container.disabled)
                container.state = "Pressed"
        }
        onReleased: {
            if (!container.disabled)
                container.state = ""
        }
    }

    Text {
        font.family: "Helvetica"
        font.pointSize: 14
        color:  container.disabled ? "#dddddd" : "#ffffff"

        anchors { top: image.top ; topMargin: 10 ; horizontalCenter: image.horizontalCenter }
        text: container.text
    }

    states: [
        State { name: "Pressed" },
        State {
            name: "Disabled"
            when: container.disabled == true
        }
    ]
}

