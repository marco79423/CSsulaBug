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
    adownloadhandler.h \
    aupdatehandler.h \
    comicmodel.h \
    convertz.h \
    networkaccessor.h \
    sfdownloadhandler.h \
    sfupdatehandler.h \
    filesaver.h \
    afilesaver.h \
    filedownloader.h \
    adownloadservice.h \
    downloadservice.h \
    acomicinfoservice.h \
    comicinfoservice.h \
    stub/stubupdatehandler.h \
    stub/stubdownloadhandler.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    networkaccessor.cpp \
    sfdownloadhandler.cpp \
    sfupdatehandler.cpp \
    filesaver.cpp \
    filedownloader.cpp \
    downloadservice.cpp \
    comicinfoservice.cpp \
    stub/stubupdatehandler.cpp \
    stub/stubdownloadhandler.cpp

RESOURCES += \
    core_resource.qrc
