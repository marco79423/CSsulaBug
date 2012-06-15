#-*- coding: utf-8 -*-

from PySide import QtCore, QtNetwork
import config
import misc
import tools


class Downloader(QtCore.QObject):
    
    info = QtCore.Signal(dict)
    finish = QtCore.Signal()

    def __init__(self, parent=None):
        super(Downloader, self).__init__(parent)
        self._networkAccessor = NetworkAccessor(self)
        self._pathList = dict()
        self._taskIdCount = 0

        self._setConnection()
        

    def download(self, task):
        """
        下載 task 任務
        task['urlList'] 所要下載的內容
        task['pathList']['url'] 其對應的檔案路徑
        """
        self._taskIdCount += 1
        self._networkAccessor.get(self._taskIdCount, task['urlList'])
        config.logging.info(u"下載任務 %d", self._taskIdCount)

        self._pathList[self._taskIdCount] = task['pathList']

    @QtCore.Slot(int, QtNetwork.QNetworkReply)
    def _onAccessorReply(self, id, networkReply):
        """
        處理 NetworkAccessor 的回應，把內容寫至目標路徑
        """
        url = networkReply.url().toString()
        path = self._pathList[id][url]


        fileInfo = QtCore.QFileInfo(path)
        dir = fileInfo.absoluteDir()
        if not fileInfo.exists():
            if not dir.exists():
                if not dir.mkpath(dir.absolutePath()):
                    config.logging.error(u"資料夾 %s 建立失敗")
                    return 
        
            file = QtCore.QFile(path)
            if not file.open(QtCore.QFile.WriteOnly):
                config.logging.error(u"開啟 %s 失敗", path)
                return

            file.write(networkReply.readAll())
            file.close()
            self.info.emit(dict(url=url, path=path))
            config.logging.info(u"已下載 %s", path)

        del self._pathList[id][url]

    @QtCore.Slot(int)
    def _onAccessorFinish(self, id):
        """
        當一項任務下載完後，刪除該任務資料
        """
        self.finish.emit()
        config.logging.info(u"id %d 下載完成", id)
        del self._pathList[id]

    def _setConnection(self):
        """
        設定連結
        """
        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)


class NetworkAccessor(QtCore.QObject):

    reply = QtCore.Signal(int, QtNetwork.QNetworkReply)
    finish = QtCore.Signal(int)

    def __init__(self, parent=None):
        super(NetworkAccessor, self).__init__(parent) 
        
        self._networkAccessManager = QtNetwork.QNetworkAccessManager(self)
        self._taskQueue = tools.Queue()
        self._isAccessing = False
        self._idCount = 0
        
        self._setConnection()

    @QtCore.Slot(str)
    @QtCore.Slot(list)
    def get(self, id, urlList):
        """
        id 為識別值，url 是要下載的網址
        get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
        """
        newTask = dict(id=id, urlList=[])

        if type(urlList) == str:
            url = urlList
            request = self._makeRequest(url)
            newTask['urlList'].append(url)
            config.logging.info(u"準備下載 %s", url)
        else:
            for url in urlList:
                request = self._makeRequest(url)
                newTask['urlList'].append(url)
                config.logging.info(u"準備下載 %s", url)
        
        self._taskQueue.enqueue(newTask)
        self._startAccess()
  
    def _setConnection(self):
        """
        設定連結
        """
        self._networkAccessManager.finished.connect(self._onManagerFinish)

    def _startAccess(self):
        """
        若是現在沒有實際執行下載任務，便開始執行。
        """
        if not self._isAccessing and not self._taskQueue.isEmpty():
            self._isAccessing = True
            for url in list(self._taskQueue.head()['urlList']):
                request = self._makeRequest(url)
                self._networkAccessManager.get(request)
                config.logging.info(u"開始下載 %s", url)

    @QtCore.Slot(QtNetwork.QNetworkReply)
    def _onManagerFinish(self, reply):
        """
        當 NetWorkAcessManager finish 時，
        刪除 _taskQueue 的此項，並負責發送加上 id 的 reply signal
        若是發現該任務已經結束了，便發送 finish
        """
        url = reply.url().toString()
        config.logging.info(u"%s 收到", url.encode('utf-8'))
        
        if reply.error():
            config.logging.error(u"%s", url.encode('utf-8'))
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
    
    url1 = 'http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe'
    url2 = 'http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe'

    task1 = dict(urlList=[url1], pathList={url1:'1a.exe'})
    task2 = dict(urlList=[url1, url2] , pathList={url1:'2a.exe', url2:'2b.exe'})

    def done():
        print 'done'

    downloader = Downloader()
    downloader.finish.connect(done)

    downloader.download(task1)
    downloader.download(task2)

    sys.exit(app.exec_())