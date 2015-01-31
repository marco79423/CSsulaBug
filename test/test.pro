QT += testlib network

TARGET = test
CONFIG += c++11 console testcase

HEADERS += \
    networkaccessortest.h \
    sfcomicsitehandlertest.h \
    blcomicsitehandlertest.h \
    mocknetworkaccessor.h \
    servicetest.h \
    stubcomicsitehandler.h \
    stubservice.h \
    convertztest.h \
    filedownloadertest.h \
    comicdownloadertest.h \
    comicmodeltest.h \
    sortfilterproxycomicmodeltest.h

SOURCES += \
    main.cpp \
    networkaccessortest.cpp \
    sfcomicsitehandlertest.cpp \
    blcomicsitehandlertest.cpp \
    servicetest.cpp \
    stubcomicsitehandler.cpp \
    stubservice.cpp \
    convertztest.cpp \
    filedownloadertest.cpp \
    comicdownloadertest.cpp \
    comicmodeltest.cpp \
    sortfilterproxycomicmodeltest.cpp

RESOURCES += \
    test_resource.qrc

INCLUDEPATH += $$PWD/../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
}

win32-g++:CONFIG(release, debug|release):{
    LIBS += -L$$OUT_PWD/../core/release -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/release/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
}

