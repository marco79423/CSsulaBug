#-------------------------------------------------
#
# Project created by QtCreator 2012-03-26T18:57:40
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = DownloadController
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    downloadercontroller.cpp \
    sfdownloadpreparer.cpp

HEADERS += \
    downloadercontroller.h \
    sfdownloadpreparer.h
