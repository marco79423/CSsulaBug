#-*- coding: utf-8 -*-

from PySide import QtCore, QtNetwork
import config
import re
import network
import misc

class UpdateHandler(QtCore.QObject):

    info = QtCore.Signal(dict)
    finish = QtCore.Signal()

    def update(self):
        pass

class DownloadHandler(QtCore.QObject):

    info = QtCore.Signal(dict)
    finish = QtCore.Signal()

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
        self._currentState = u"NothingDoing"
        self._allPageUrlList = []

        self._setConnection()

    def update(self):
        if self._currentState == u"NothingDoing":
            config.logging.info(u"開始更新")
            self._startProcess(u"ALLPageUrlListGetting")
        else:
            config.logging.info(u"現在狀態是 %s，還不能更新", self._currentState)

    def _setConnection(self):
        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)

    def _startProcess(self, state):
        config.logging.info(u"開始執行 %s 狀態", state)
        if state == u"ALLPageUrlListGetting":
            self._currentState = u"ALLPageUrlListGetting"
            self._networkAccessor.get(0, "http://comic.sfacg.com/Catalog/")
        elif state == u"ComicInfoGetting":
            self._currentState = u"ComicInfoGetting"
            self._networkAccessor.get(1, self._allPageUrlList)
        else:
            config.logging.error(u"錯誤的狀態 %s", state)
        
    @QtCore.Slot(int, QtNetwork.QNetworkReply)
    def _onAccessorReply(self, id, networkReply):
        if self._currentState == "ALLPageUrlListGetting":
            self._allPageUrlList = self._getPageUrl(unicode(networkReply.readAll(), 'utf-8'))
            config.logging.info(u"取得 allPageUrlList")
        elif self._currentState == "ComicInfoGetting":
            self._getComicInfo(unicode(networkReply.readAll(), 'utf-8'))
            config.logging.info(u"取得 %s 的資訊", networkReply.url().toString())
        else:
            config.logging.error(u"錯誤的狀態 %s", self._currentState)

    @QtCore.Slot(int)
    def _onAccessorFinish(self, id):
        if self._currentState == "ALLPageUrlListGetting":
            config.logging.info(u"進入 ComicInfoGetting 階段")
            self._startProcess("ComicInfoGetting")
        elif self._currentState == "ComicInfoGetting":
            config.logging.info(u" 下載完成")
            self.finish.emit()

    def _getPageUrl(self, html):

        maxPageNumber = 0
        
        pageNumberExp = QtCore.QRegExp("http://comic.sfacg.com/Catalog/"
                                       "Default.aspx\\?PageIndex=(\\d+)")
        pos = 0
        while True:
            pos = pageNumberExp.indexIn(html, pos)
            if pos == -1: break
            captureNumber = int(pageNumberExp.cap(1))
            if captureNumber > maxPageNumber:
                maxPageNumber = captureNumber
            pos += pageNumberExp.matchedLength()

        #因為有 bug ，所以還要再加上一頁
        maxPageNumber += 1
                
        allPageUrlList = []
        for i in range(1, maxPageNumber+1):
            allPageUrlList.append("http://comic.sfacg.com/Catalog/Default.aspx?"
                                  "PageIndex=" + str(i))
        return allPageUrlList

    def _getComicInfo(self, html):
         
         regexp = QtCore.QRegExp("<img src=\"([^\"]+)\"" #cover
                                 "[^>]+></a></li>\\s+<li><strong class=\""
                                 "F14PX\"><a href=\"/HTML/([^/]+)" #keyName
                                 "[^>]+>([^<]+)" #name
                                 "[^1]+1\">([^<]+)" #comicAuthor
                                 "[^\\]]+[^>]+>([^<]+)" #comicType
                                 "</a> /([^/]+)+/" #lastUpdated
                                 " \\d+<br />([^<]+)" #description
                                 )
         
         pos = 0
         while True:
             pos = regexp.indexIn(html, pos)
             if pos == -1: break
             
             updateInfo = dict(site="SF",
                               coverUrl=regexp.cap(1),
                               key=regexp.cap(2),
                               name=regexp.cap(3),
                               author=regexp.cap(4),
                               type=regexp.cap(5),
                               lastUpdated=regexp.cap(6).strip(),
                               description=regexp.cap(7).strip())
             
             config.logging.info(u"取得 updateInfo %s", misc.comicInfoToString(updateInfo))
             self.info.emit(updateInfo)

             pos += regexp.matchedLength()


class DownloadHandler(DownloadHandler):
    pass

if __name__ == "__main__":
    import sys
    app = QtCore.QCoreApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)
    
    def done():
        print 'done'

    count = 0
    def add():
        global count 
        count += 1
        print "count", count

    handler = SFUpdateHandler()
    handler.finish.connect(done)
    handler.info.connect(add)
    handler.update()
    sys.exit(app.exec_())
    
    """
    logger = misc.getLogger("test")
    logger.info("test")           
    raw_input()  
    """              