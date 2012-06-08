#-*- coding: cp950 -*-

from PyQt4 import QtCore, QtNetwork
import re
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
���e���� SF 
���} http://comic.sky-fire.com
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
            logger.info("SFUpdateHandler:update:�}�l��s")
            self._startProcess("ALLPageUrlListGetting")
        else:
            logger.info("SFUpdateHandler:update:�{�b���A�O %s�A�٤����s", self._currentState)

    def _setConnection(self):
        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)

    def _startProcess(self, state):
        logger.info("SFUpdateHandler:_startProcess:�}�l���� %s ���A", state)
        if state == "ALLPageUrlListGetting":
            self._currentState = "ALLPageUrlListGetting"
            self._networkAccessor.get(0, "http://comic.sfacg.com/Catalog/")
        elif state == "ComicInfoGetting":
            self._currentState = "ComicInfoGetting"
            self._networkAccessor.get(1, self._allPageUrlList)
        else:
            logger.error("SFUpdateHandler:_startProcess:���~�����A %s", state)
        
    @QtCore.pyqtSlot(int, QtNetwork.QNetworkReply)
    def _onAccessorReply(self, id, networkReply):
        if self._currentState == "ALLPageUrlListGetting":
            self._allPageUrlList = _self._getPageUrl(str(networkReply.readAll()))
            logger.info("SFUpdateHandler:_onAccessorReply:���o allPageUrlList")
        elif self._currentState == "ComicInfoGetting":
            self._getComicInfo(str(networkReply.readAll()))
            logger.info("SFUpdateHandler:_onAccessorReply: ���o %s ����T", str(reply.url().toString()))
        else:
            logger.error("SFUpdateHandler:_onAccessorReply:���~�����A %s", self._currentState)

    @QtCore.pyqtSlot(int)
    def _onAccessorFinish(self, id):
        if self._currentState == "ALLPageUrlListGetting":
            logger.info("SFUpdateHandler:_onAccessorFinish:�i�J ComicInfoGetting ���q")
            self._startProccess("ComicInfoGetting")
        elif self._currentState == "ComicInfoGetting":
            pass

    def _getPageUrl(self, html):

        maxPageNumber = 0
        
        pageNumberExp = QtCore.QRegExp("http://comic.sfacg.com/Catalog/"
                                       "Default.aspx\\?PageIndex=(\\d+)")
        pos = 0
        while True:
            pos = pageNumberExp.indexIn(html, pos)
            if pos == -1: break
            captureNumber, isOk = pageNumberExp.cap(1).toInt()
            if captureNumber > maxPageNumber:
                maxPageNumber = captureNumber
            pos += pageNumberExp.matchedLength()

        #�]���� bug �A�ҥH�٭n�A�[�W�@��
        maxPageNumber += 1
                
        allPageUrlList = []
        for i in range(1, maxPageNumber+1):
            allPageUrlList.append("http://comic.sfacg.com/Catalog/Default.aspx?"
                                  "PageIndex=" + str(i))
        return allPageUrlList

    def _getComicInfo(self, html):
        pass

class DownloadHandler(DownloadHandler):
    pass

if __name__ == "__main__":
    import sys
    app = QtCore.QCoreApplication(sys.argv)

    handler = SFUpdateHandler()
    handler.update()
    sys.exit(app.exec_())