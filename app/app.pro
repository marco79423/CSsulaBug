#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

TARGET = CSsulaBug
TEMPLATE = app
QT += quick
CONFIG += c++11

macx {
    ICON = $$PWD/icon.icns
}
win32 {
    RC_FILE = CSsulaBug.rc
}

SOURCES += \
    main.cpp

RESOURCES += \
    app_resource.qrc

INCLUDEPATH += $$PWD/../core

win32-g++:CONFIG(debug, debug|release): {
    LIBS += -L$$OUT_PWD/../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
}
unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
}
