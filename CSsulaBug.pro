#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

QT       += core gui widgets network sql quick

TARGET = CSsulaBug
TEMPLATE = app


SOURCES += main.cpp \
    networkaccessor.cpp \
    downloader.cpp \
    sfupdatehandler.cpp \
    sfdownloadhandler.cpp \
    core.cpp \
    comicmodel.cpp \
    convertz.cpp

HEADERS  += \
    networkaccessor.h \
    downloader.h \
    updatehandler.h \
    downloadhandler.h \
    sfupdatehandler.h \
    sfdownloadhandler.h \
    core.h \
    comicmodel.h \
    convertz.h

RC_FILE = CSsulaBug.rc

OTHER_FILES += \
    ui/MainView.qml \
    ui/ContentView.qml \
    ui/Button.qml


static {
    QMAKE_LFLAGS += -static-libgcc
    CONFIG += static
    CONFIG += staticlib
    DEFINES += STATIC
    message(" static build ")
}

RESOURCES += \
    resource.qrc
