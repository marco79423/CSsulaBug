#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

QT       += core widgets network quick
TARGET = CSsulaBug
TEMPLATE = app

macx {
    ICON = $$PWD/icon.icns
}
win32 {
    RC_FILE = CSsulaBug.rc
}

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
    adownloadhandler.h \
    sfupdatehandler.h \
    sfdownloadhandler.h \
    core.h \
    comicmodel.h \
    convertz.h \
    aupdatehandler.h

OTHER_FILES += \
    ui/MainView.qml


static {
    QMAKE_LFLAGS += -static-libgcc
    CONFIG += static
    CONFIG += staticlib
    DEFINES += STATIC
    message(" static build ")
}

RESOURCES += \
    resource.qrc
