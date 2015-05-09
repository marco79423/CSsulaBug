#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T23:07:00
#
#-------------------------------------------------

TARGET = CSsulaBug
CONFIG += c++11
TEMPLATE = app

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx {
    ICON = $$PWD/icon.icns
}
win32 {
    RC_FILE = CSsulaBug.rc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    comicinfoview.cpp \
    comicinfodelegate.cpp

HEADERS  += mainwindow.h \
    comicinfoview.h \
    comicinfodelegate.h

FORMS    += mainwindow.ui \
    comicinfoview.ui


RESOURCES += \
    ../resource/app_resource.qrc

INCLUDEPATH += $$PWD/../core

win32-g++:CONFIG(debug, debug|release): {
    LIBS += -L$$OUT_PWD/../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
}

win32-g++:CONFIG(release, debug|release): {
    LIBS += -L$$OUT_PWD/../core/release -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/release/libcore.a
}


unix:CONFIG(debug, debug|release){
    LIBS += -L$$OUT_PWD/../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
}
