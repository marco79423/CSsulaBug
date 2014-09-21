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
    aservice.h

SOURCES += \
    comicmodel.cpp \
    convertz.cpp \
    networkaccessor.cpp \
    filesaver.cpp \
    filedownloader.cpp \
    sfcomicsitehandler.cpp \
    service.cpp

RESOURCES += \
    core_resource.qrc

#release {
#    DEFINES += QT_NO_DEBUG_OUTPUT
#}
