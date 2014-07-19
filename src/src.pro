#-------------------------------------------------
#
# Project created by QtCreator 2014-07-19T18:01:26
#
#-------------------------------------------------

QT       += widgets network

TARGET = cssulabug
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    adownloadhandler.h \
    aupdatehandler.h \
    comicmodel.h \
    convertz.h \
    core.h \
    downloader.h \
    networkaccessor.h \
    sfdownloadhandler.h \
    sfupdatehandler.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    core.cpp \
    downloader.cpp \
    networkaccessor.cpp \
    sfdownloadhandler.cpp \
    sfupdatehandler.cpp

RESOURCES += \
    src_resource.qrc
