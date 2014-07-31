#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T12:32:20
#
#-------------------------------------------------

QT += testlib

TARGET = unittest
CONFIG += console testcase


SOURCES += \
    convertztest.cpp \
    main.cpp

HEADERS += \
    convertztest.h

INCLUDEPATH += $$PWD/../../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/debug/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/libcore.a
}
