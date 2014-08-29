QT += testlib network

TARGET = integrationtest
CONFIG += c++11 console testcase

HEADERS += \
    filesavertest.h \
    networkaccessortest.h \
    sfcomicsitehandlertest.h

SOURCES += \
    filesavertest.cpp \
    main.cpp \
    networkaccessortest.cpp \
    sfcomicsitehandlertest.cpp

RESOURCES += \
    integration_resource.qrc

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

