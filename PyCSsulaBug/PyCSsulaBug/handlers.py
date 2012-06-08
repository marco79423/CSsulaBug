#-*- coding: cp950 -*-

from PyQt4 import QtCore
import network
import misc

logger = misc.getLogger()

class UpdateHandler(QtCore.QObject):

    info = QtCore.pyqtSignal(dict)
    finish = QtCore.pyqtSignal()

    def update(self):
        pass

class DownloadHandler(QtCore.QObject):

    info = QtCore.pyqtSignal(dict)
    finish = QtCore.pyqtSignal()

    def download(self, name, dstDir):
        pass

"""
漫畫網站 SF 
網址 http://comic.sky-fire.com
"""

class SFUpdateHandler(UpdateHandler):
    
    def __init__(self, parent=None):
        super(SFUpdateHandler, self).__init__(parent)
        self._networkAccessor = network.NetworkAccessor(self)
        self._currentState = "NothingDoing"
        self._allPageUrlList = []

        self._setConnection()

    def update(self):
        if self._currentState == "NothingDoing":
            logger.info("SFUpdateHandler:update:開始更新")
            self._currentState = "ALLPageUrlListGetting"
            self._process()
        else:
            logger.info("SFUpdateHandler:update:現在狀態是 %s，還不能更新", self._currentState)

    def _startProcess(self):
        logger.info("SFUpdateHandler:_startProcess:開始執行 %s 狀態", self._currentState)
        if self._currentState == "ALLPageUrlListGetting":
            self._networkAccessor.get(0, "http://comic.sfacg.com/Catalog/")
        elif self._currentState == "ComicInfoGetting":
            self._networkAccessor.get(1, self._allPageUrlList)
        else:
            logger.error("SFUpdateHandler:_startProcess:錯誤的狀態 %s", self._currentState)
        
    def _onAccessorReply(self, reply):
        pass

    def _onAccessorFinish(self):
        pass

    def _setConnection(self):
        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)

class DownloadHandler(DownloadHandler):
    pass