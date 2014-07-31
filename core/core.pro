#-------------------------------------------------
#
# Project created by QtCreator 2014-07-19T18:01:26
#
#-------------------------------------------------

QT       += widgets network

TARGET = core
TEMPLATE = lib
CONFIG += c++11 staticlib

HEADERS += \
    adownloadhandler.h \
    aupdatehandler.h \
    comicmodel.h \
    convertz.h \
    core.h \
    downloader.h \
    networkaccessor.h \
    sfdownloadhandler.h \
    sfupdatehandler.h \
    filesaver.h \
    afilesaver.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    core.cpp \
    downloader.cpp \
    networkaccessor.cpp \
    sfdownloadhandler.cpp \
    sfupdatehandler.cpp \
    filesaver.cpp

RESOURCES += \
    core_resource.qrc
