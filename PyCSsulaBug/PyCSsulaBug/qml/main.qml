import QtQuick 1.1

Rectangle {
    id: mainView
    width: 400
    height: 600
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#463260"
        }

        GradientStop {
            position: 0.460
            color: "#5e4382"
        }

        GradientStop {
            position: 1
            color: "#0e0a11"
        }
    }

    ComicList {}

    Header{}

    Footer {}
}

