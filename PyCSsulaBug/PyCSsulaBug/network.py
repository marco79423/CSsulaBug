#-*- coding: cp950 -*-

from PyQt4 import QtCore, QtGui, QtNetwork
import misc
import tools

logger = misc.getLogger()

class Downloader:
    pass

class ImageDownloader(Downloader):
    pass

class NetworkAccessor(QtCore.QObject):

    reply = QtCore.pyqtSignal(QtNetwork.QNetworkReply)
    finish = QtCore.pyqtSignal(int)

    def __init__(self, parent=None):
        super(NetworkAccessor, self).__init__(parent)
        self._initialize()
        
        self._networkAccessManager.finished.connect(self._onManagerFinish)

    @QtCore.pyqtSlot(str)
    @QtCore.pyqtSlot(list)
    def get(self, urlList):
        """
        url 是要下載的網址，呼叫完後會回傳該任務的識別值 id
        """
        self._idCount += 1
        self._checkList[self._idCount] = set()

        if type(urlList) == str:
            url = urlList
            request = self._makeRequest(url)
            self._checkList[self._idCount].add(url)
            self._networkAccessManager.get(request)
            logger.info("NetworkAccessor:get:開始下載 %s", url)
        else:
            for url in urlList:
                request = self._makeRequest(url)
                self._checkList[self._idCount].add(url)
                self._networkAccessManager.get(request)
                logger.info("NetworkAccessor:get:開始下載 %s", url)

        return self._idCount
  
    def _initialize(self):
        """
        初始化變數
        """
        self._networkAccessManager = QtNetwork.QNetworkAccessManager(self)
        self._checkList = dict()
        self._idCount = 0


    @QtCore.pyqtSlot(QtNetwork.QNetworkReply)
    def _onManagerFinish(self, reply):
        """
        當 NetWorkAcessManager finish 時，
        刪除 _checkList 的此項，並負責發送加上 id 的 signal
        """
        url = reply.url()
        logger.info("NetworkAccessor:_onManagerFinish: %s 收到", url)
        
        if reply.error():
            logger.error("NetworkAccessor:_onManagerFinish: %s", url)
      
        _checkList
        self.reply.emit(reply)

    def _makeRequest(self, url):
        request = QtNetwork.QNetworkRequest(QtCore.QUrl(url))
        request.setRawHeader("User-Agent", 
                             ("Mozilla/5.0 (Windows NT 6.1; WOW64) "
                              "AppleWebKit/536.5 (KHTML, like Gecko) "
                              "Chrome/19.0.1084.1 Safari/536.5"))
        return request

if __name__ in "__main__":
    import sys
    app = QtCore.QCoreApplication(sys.argv)
    n = NetworkAccessor()
    n.get("http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe")
    sys.exit(app.exec_())