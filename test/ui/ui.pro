QT += quick

TARGET = uitest
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/debug/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/libcore.a
}

SOURCES += \
    main.cpp \
    stubservice.cpp

HEADERS += \
    stubservice.h

RESOURCES += \
    ../../resource/app_resource.qrc
