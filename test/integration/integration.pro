QT += testlib

TARGET = integrationtest
CONFIG += c++11 console testcase

HEADERS += \
    filesavertest.h

SOURCES += \
    filesavertest.cpp \
    main.cpp

INCLUDEPATH += $$PWD/../../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/debug/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/libcore.a
}
