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

    reply = QtCore.pyqtSignal(int, QtNetwork.QNetworkReply)
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
        get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
        """
        self._idCount += 1
        newTask = dict(id=self._idCount, urlList=[])

        if type(urlList) == str:
            url = urlList
            request = self._makeRequest(url)
            newTask['urlList'].append(url)
            logger.info("NetworkAccessor:get:準備下載 %s", url)
        else:
            for url in urlList:
                request = self._makeRequest(url)
                newTask['urlList'].append(url)
                logger.info("NetworkAccessor:get:準備下載 %s", url)
        
        self._taskQueue.enqueue(newTask)
        self._startAccess()

        return self._idCount
  
    def _initialize(self):
        """
        初始化變數
        """
        self._networkAccessManager = QtNetwork.QNetworkAccessManager(self)
        self._taskQueue = tools.Queue()
        self._isAccessing = False
        self._idCount = 0

    def _startAccess(self):
        """
        若是現在沒有實際執行下載任務，便開始執行。
        """
        if not self._isAccessing and not self._taskQueue.isEmpty():
            self._isAccessing = True
            for url in list(self._taskQueue.head()['urlList']):
                request = self._makeRequest(url)
                self._networkAccessManager.get(request)
                logger.info("NetworkAccessor:_startAccess:開始下載 %s", url)

    @QtCore.pyqtSlot(QtNetwork.QNetworkReply)
    def _onManagerFinish(self, reply):
        """
        當 NetWorkAcessManager finish 時，
        刪除 _taskQueue 的此項，並負責發送加上 id 的 reply signal
        若是發現該任務已經結束了，便發送 finish
        """
        url = str(reply.url().toString())
        logger.info("NetworkAccessor:_onManagerFinish: %s 收到", url)
        
        if reply.error():
            logger.error("NetworkAccessor:_onManagerFinish: %s", url)
            return
        
        self._taskQueue.head()['urlList'].remove(url)
        self.reply.emit(self._taskQueue.head()['id'], reply)

        if len(self._taskQueue.head()['urlList']) == 0:
            self.finish.emit(self._taskQueue.head()['id'])
            if not self._taskQueue.isEmpty():
                self._taskQueue.dequeue()
            self._isAccessing = False
            self._startAccess()

    def _makeRequest(self, url):
        """
        利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request 
        """
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
    n.get(["http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe", "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe"])
    sys.exit(app.exec_())