#-------------------------------------------------
#
# Project created by QtCreator 2014-07-19T18:01:26
#
#-------------------------------------------------

QT += network

TARGET = core
TEMPLATE = lib
CONFIG += c++11 staticlib

HEADERS += \
    comicmodel.h \
    convertz.h \
    networkaccessor.h \
    filedownloader.h \
    globals.h \
    acomicsitehandler.h \
    service.h \
    aservice.h \
    site/sfcomicsitehandler.h \
    site/blcomicsitehandler.h \
    comicdownloader.h \
    anetworkaccessor.h \
    proxycomicmodel.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    networkaccessor.cpp \
    filedownloader.cpp \
    service.cpp \
    site/sfcomicsitehandler.cpp \
    site/blcomicsitehandler.cpp \
    comicdownloader.cpp \
    proxycomicmodel.cpp

RESOURCES += \
    core_resource.qrc

#release {
#    DEFINES += QT_NO_DEBUG_OUTPUT
#}
