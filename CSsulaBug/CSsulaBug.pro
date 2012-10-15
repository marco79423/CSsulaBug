#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

QT       += core gui network sql declarative

TARGET = CSsulaBug
TEMPLATE = app


SOURCES += main.cpp \
    networkaccessor.cpp \
    downloader.cpp \
    updatehandler.cpp \
    downloadhandler.cpp \
    sfupdatehandler.cpp \
    sfdownloadhandler.cpp \
    core.cpp \
    comicmodel.cpp

HEADERS  += \
    networkaccessor.h \
    downloader.h \
    updatehandler.h \
    downloadhandler.h \
    sfupdatehandler.h \
    sfdownloadhandler.h \
    core.h \
    comicmodel.h

FORMS    +=

OTHER_FILES += \
    ui/MainView.qml \
    ui/ContentView.qml \
    ui/Comic.qml \
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
