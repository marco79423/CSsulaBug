#-*- coding: utf-8 -*-

from PySide import QtCore, QtNetwork
import config
import re
import network
import misc

class UpdateHandler(QtCore.QObject):

    info = QtCore.Signal(dict)
    finish = QtCore.Signal()

    @QtCore.Slot()
    def isReady(self):
        return True

    def update(self):
        pass

class DownloadHandler(QtCore.QObject):

    info = QtCore.Signal(dict)
    finish = QtCore.Signal()

    def isReady(self):
        return True

    @QtCore.Slot(str, str)
    def download(self, key, dstDir):
        pass


class SiteHandler(QtCore.QObject):

    updateInfo = QtCore.Signal(dict)
    updateFinish = QtCore.Signal()

    downloadInfo = QtCore.Signal(dict)
    downloadFinish = QtCore.Signal()
    
    def __init__(self, parent=None):
        super(SiteHandler, self).__init__(parent)
        self._updateHandler = None
        self._downloadHandler = None

        self._setConnection()

    @QtCore.Slot(UpdateHandler)
    def setUpdateHandler(self, updateHandler):
        self._updateHandler = updateHandler
        self._updateHandler.setParent(self)

    @QtCore.Slot(DownloadHandler)
    def setDownloadHandler(self, downloadHandler):
        self._downloadHandler = downloadHandler
        self._downloadHandler.setParent(self)

    @QtCore.Slot()
    def update(self):
        self._updateHandler.update()

    @QtCore.Slot(str, str)
    def download(self, name, dstDir):
        self._downloadHandler.download(name, dstDir)

    def _setConnection(self):
        self._updateHandler.info.connect(self.updateInfo)
        self._updateHandler.finish.connect(self.udpateFinish)

        self._downloadHandler.info.connect(self.downloadInfo)
        self._downloadHandler.finish.connect(self.downloadFinish)
"""
漫畫網站 SF 
網址 http://comic.sky-fire.com
"""

class SFUpdateHandler(UpdateHandler):
    """
    SFUpdateHandler 總共有三種狀態，
    分別是 NothingDoing 、 ALLPageUrlListGetting 和 ComicInfoGetting
    若狀態為 NothingDoing 便可執行 update 更新線上內容，而其餘狀態下呼叫 update 不會有任何反應
    而要查詢現在是否可以更新，可以使用 isReady() 來判斷。

    更新的內容會以 signal 的形式回傳，形態是 dictionary
    """
    def __init__(self, parent=None):
        super(SFUpdateHandler, self).__init__(parent)
        self._networkAccessor = network.NetworkAccessor(self)
        self._currentState = u"NothingDoing"
        self._allPageUrlList = []

        self._setConnection()
  
    def isReady(self):
        return self._currentState == u"NothingDoing"

    @QtCore.Slot()
    def update(self):
        """
        若狀態為 NothingDoing 就更新線上內容，並會以 signal 的形式回傳訊息，
        若狀態不為 NothingDoing 便什麼也不做。
        """
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
        if self._currentState == u"ALLPageUrlListGetting":
            self._getPageUrl(unicode(networkReply.readAll(), 'utf-8'))
            config.logging.info(u"取得 allPageUrlList")
        elif self._currentState == u"ComicInfoGetting":
            self._getComicInfo(unicode(networkReply.readAll(), 'utf-8'))
            config.logging.info(u"取得 %s 的資訊", networkReply.url().toString())
        else:
            config.logging.error(u"錯誤的狀態 %s", self._currentState)

    @QtCore.Slot(int)
    def _onAccessorFinish(self, id):
        if self._currentState == u"ALLPageUrlListGetting":
            config.logging.info(u"進入 ComicInfoGetting 階段")
            self._startProcess("ComicInfoGetting")
        elif self._currentState == u"ComicInfoGetting":
            self._currentState = u"NothingDoing"
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
        
        self._allPageUrlList = []     
        for i in range(1, maxPageNumber+1):
            self._allPageUrlList.append("http://comic.sfacg.com/Catalog/Default.aspx?"
                                  "PageIndex=" + str(i))
  

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


class SFDownloadHandler(DownloadHandler):
    
    def __init__(self, parent=None):
        super(SFDownloadHandler, self).__init__(parent)
        self._networkAccessor = network.NetworkAccessor(self)
        self._downloader = network.Downloader(self)
        self._currentState = u"NothingDoing"
        self._task = dict(urlList=[], pathList=dict())
        self._key = ""
        self._dstDir = ""
        self._comicName = ""
        self._chapterUrlList = []
        self._setConnection()

    def isReady(self):
        return self._currentState == u"NothingDoing"

    @QtCore.Slot(str, str)
    def download(self, key, dstDir):
        if self._currentState == u"NothingDoing":
            config.logging.info(u"開始下載 %s" % key)
            self._key, self._dstDir = key, dstDir
            self._startProcess(u"ChapterUrlListing")
        else:
            config.logging.info(u"現在狀態是 %s，還不能下載", self._currentState)

    def _setConnection(self):
        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)
        self._downloader.info.connect(self.info)
        self._downloader.finish.connect(self._onDownloaderFinish)

    def _startProcess(self, state):
        config.logging.info(u"開始執行 %s 狀態", state)
        if state == u"ChapterUrlListing":
            self._currentState = u"ChapterUrlListing"
            self._networkAccessor.get(0, "http://comic.sfacg.com/HTML/%s/" % (self._key))
        elif state == u"TaskMaking":
            self._currentState = u"TaskMaking"
            self._networkAccessor.get(1, self._chapterUrlList)
        elif state == u"Downloading":
            self._currentState = u"Downloading"
            self._downloader.download(self._task)
        else:
            config.logging.error(u"錯誤的狀態 %s", state)

    @QtCore.Slot(int, QtNetwork.QNetworkReply)
    def _onAccessorReply(self, id, networkReply):
        url = networkReply.url().toString()
        html = unicode(networkReply.readAll(), 'utf-8')

        if self._currentState == "ChapterUrlListing":
            self._getComicName(html)
            self._listChapters(html)
        elif self._currentState == "TaskMaking":
            self._makeTask(url, html)
        else:
            config.logging.error(u"錯誤的狀態 %s", self._currentState)

    @QtCore.Slot(int)
    def _onAccessorFinish(self, id):
        if self._currentState == u"ChapterUrlListing":
            self._startProcess(u"TaskMaking")
        elif self._currentState == u"TaskMaking":
            self._startProcess(u"Downloading")
        else:
            config.logging.error(u"錯誤的狀態 %s", self._currentState)

    @QtCore.Slot()
    def _onDownloaderFinish(self):
        self._currentState = u"NothingDoing"
        self.finish.emit()

    def _getComicName(self, html):
        nameExp = QtCore.QRegExp("<b class=\"F14PX\">([^<]+)</b>")
        nameExp.indexIn(html)
        self._comicName = nameExp.cap(1)
        config.logging.info(u"取得漫畫名稱 %s", self._comicName)

    def _listChapters(self, html):
        #取得 ID
        idExp = QtCore.QRegExp("comicCounterID = (\\d+)")
        idExp.indexIn(html)
        comicID = int(idExp.cap(1))
        config.logging.info(u"取得 comicID %d"%(comicID))

        #取得 漫畫種類(網站自己的分法)
        typeExp = QtCore.QRegExp("<a href=\"http://([^\"]+).sfacg.com/AllComic")
        typeExp.indexIn(html);
        comicType = typeExp.cap(1)
        config.logging.info(u"取得 comicType %s"%(comicType))

        #取得話數
        chapterExp = QtCore.QRegExp("<a href=\"http://%s.sfacg.com/AllComic/%s/(\\d+j?)/"%(comicType, comicID))
              
        pos = 0
        while True:
            pos = chapterExp.indexIn(html, pos)
            if pos == -1: break
            chapterUrl = "http://%s.sfacg.com/Utility/%s/%s.js" % (comicType, comicID, chapterExp.cap(1))
            self._chapterUrlList.append(chapterUrl)
            config.logging.info(u"取得 chapterUrl %s" %(chapterUrl))
            pos += chapterExp.matchedLength()
            
    def _makeTask(self, url, html):

        #取得 chapter
        chapterExp = QtCore.QRegExp("\\.sfacg\\.com/Utility/\\d+/(\\d+j?).js");
        chapterExp.indexIn(url);
        chapter = chapterExp.cap(1);

        #取得 imageUrl
        urlExp = QtCore.QRegExp("picAy\\[(\\d+)\\] = \"([^\"]+)\"");

        pos = 0
        while True:
            pos = urlExp.indexIn(html, pos)
            if pos == -1: break
            imageNum = int(urlExp.cap(1))
            imageUrl = urlExp.cap(2)
            path = "%s/%s/%s/%03d.%s" %(self._dstDir, self._comicName, chapter, imageNum, imageUrl[-3:])
            self._task['urlList'].append(imageUrl)
            self._task['pathList'][imageUrl] = path
            pos += urlExp.matchedLength()


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

    """
    handler = SFUpdateHandler()
    handler.finish.connect(done)
    handler.info.connect(add)
    handler.update()
    """

    handler = SFDownloadHandler()
    handler.download("FSJII", u"漫畫")
    sys.exit(app.exec_())
    
              