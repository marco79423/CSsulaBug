#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative
import core
#import handlers
import models

if __name__ in "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)

    view = QtDeclarative.QDeclarativeView()
    core = core.Core()
  
    view.rootContext().setContextProperty('core', core)
    view.rootContext().setContextProperty('comicModel', core.model())
    
    view.setSource(QtCore.QUrl("ui/MainView.qml"))
    view.show()

    sys.exit(app.exec_())