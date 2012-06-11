﻿#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import views
import controllers

class MainWindow(QtGui.QMainWindow):
    
    def __init__(self, parent=None):
      
        super(MainWindow, self).__init__(parent)
        self._initialize()

        #初始設定
        self.setCentralWidget(self._mainView)

        #連結功能

    def _initialize(self):
        """
        初始化變數
        """
        self._mainView = views.MainView(self)
        #self._mainController = controllers.MainController(self)


class ComicInfo:
    pass

class Form:
    pass

class SFUpdater:
    pass

class DownloadController:
    pass

class DownloadPreparer:
    pass

class SFDownloadPreparer:
    pass

class NetworkAccessor:
    pass



if __name__ in "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)

    m = MainWindow()
    m.show()
    sys.exit(app.exec_())