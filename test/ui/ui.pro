QT += quick

TARGET = uitest
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/debug/libcore.a
}

win32-g++:CONFIG(release, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/release -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/release/libcore.a
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
