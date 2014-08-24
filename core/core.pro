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
    filesaver.h \
    afilesaver.h \
    filedownloader.h \
    globals.h \
    acomicsitehandler.h \
    sfcomicsitehandler.h \
    service.h \
    aservice.h \
    stub/stubservice.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    networkaccessor.cpp \
    filesaver.cpp \
    filedownloader.cpp \
    sfcomicsitehandler.cpp \
    service.cpp \
    stub/stubservice.cpp

RESOURCES += \
    core_resource.qrc
