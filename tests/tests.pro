TARGET = tests
TEMPLATE = app

CONFIG += console

SOURCES += \
    main.cpp

INCLUDEPATH += $$PWD/../src

win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug -lcssulabug

