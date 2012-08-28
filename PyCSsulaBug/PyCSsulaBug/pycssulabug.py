#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative
import handlers
import models

if __name__ in "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)

    view = QtDeclarative.QDeclarativeView()
    
    model = models.ComicModel()
    model.update()

    view.rootContext().setContextProperty('comicModel', model)
    view.setSource(QtCore.QUrl("qml/main.qml"))
    view.show()

    sys.exit(app.exec_())