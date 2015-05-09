#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG+= ordered

SUBDIRS += core \
    app \
    ui \
    test

app.depends = core
ui.depends = core
test.depends = core
