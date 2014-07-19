#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG+= ordered

SUBDIRS += \
    src \
    app \
    tests \

app.depends = src
tests.depends = src
