#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG+= ordered

SUBDIRS += core app \
    test

app.depends = core
test.depends = core
