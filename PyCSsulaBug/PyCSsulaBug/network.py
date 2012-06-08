#-*- coding: cp950 -*-

from PyQt4 import QtCore, QtGui, QtNetwork
import misc
import tools

logger = misc.getLogger()

class Downloader(QtCore.QObject):
    def __init__(self, parent=None):
        super(Downloader, self).__init__(parent)
        self._initialize()

        self._networkAccessor.reply.connect(self._onAccessorReply)
        self._networkAccessor.finish.connect(self._onAccessorFinish)

    def download(self, task):
        """
        �U�� task ����
        task['urlList'] �ҭn�U�������e
        task['pathList']['url'] ��������ɮ׸��|
        """
        self._taskIdCount += 1
        self._networkAccessor.get(self._taskIdCount, task['urlList'])
        self._pathList[self._taskIdCount] = task['pathList']

    @QtCore.pyqtSlot(int, QtNetwork.QNetworkReply)
    def _onAccessorReply(self, id, networkReply):
        """
        �B�z NetworkAccessor ���^���A�⤺�e�g�ܥؼи��|
        """
        url = str(networkReply.url().toString())
        path = self._pathList[id][url]

        file = QtCore.QFile(path)
        if not file.open(QtCore.QFile.WriteOnly):
            logger.error("Downloader:_onAccessorReply: �}�� %s ����", path)
            return
        file.write(networkReply.readAll())
        file.close()
        logger.info("Downloader:_onAccessorReply: �w�U�� %s", path)

        del self._pathList[id][url]

    @QtCore.pyqtSlot(int)
    def _onAccessorFinish(self, id):
        """
        ��@�����ȤU������A�R���ӥ��ȸ��
        """
        logger.info("Downloader:_onAccessorFinish: id %d �U������", id)
        del self._pathList[id]

    def _initialize(self):
        """
        ��l���ܼ�
        """
        self._networkAccessor = NetworkAccessor(self)
        self._pathList = dict()
        self._taskIdCount = 0


class NetworkAccessor(QtCore.QObject):

    reply = QtCore.pyqtSignal(int, QtNetwork.QNetworkReply)
    finish = QtCore.pyqtSignal(int)

    def __init__(self, parent=None):
        super(NetworkAccessor, self).__init__(parent) 
        self._initialize()
        
        self._networkAccessManager.finished.connect(self._onManagerFinish)

    @QtCore.pyqtSlot(str)
    @QtCore.pyqtSlot(list)
    def get(self, id, urlList):
        """
        id ���ѧO�ȡAurl �O�n�U�������}
        get �O�M�w�N�n�U�������ȡA��ڪ��U���O�� _startAccess �ާ@
        """
        newTask = dict(id=id, urlList=[])

        if type(urlList) == str:
            url = urlList
            request = self._makeRequest(url)
            newTask['urlList'].append(url)
            logger.info("NetworkAccessor:get:�ǳƤU�� %s", url)
        else:
            for url in urlList:
                request = self._makeRequest(url)
                newTask['urlList'].append(url)
                logger.info("NetworkAccessor:get:�ǳƤU�� %s", url)
        
        self._taskQueue.enqueue(newTask)
        self._startAccess()
  
    def _initialize(self):
        """
        ��l���ܼ�
        """
        self._networkAccessManager = QtNetwork.QNetworkAccessManager(self)
        self._taskQueue = tools.Queue()
        self._isAccessing = False
        self._idCount = 0

    def _startAccess(self):
        """
        �Y�O�{�b�S����ڰ���U�����ȡA�K�}�l����C
        """
        if not self._isAccessing and not self._taskQueue.isEmpty():
            self._isAccessing = True
            for url in list(self._taskQueue.head()['urlList']):
                request = self._makeRequest(url)
                self._networkAccessManager.get(request)
                logger.info("NetworkAccessor:_startAccess:�}�l�U�� %s", url)

    @QtCore.pyqtSlot(QtNetwork.QNetworkReply)
    def _onManagerFinish(self, reply):
        """
        �� NetWorkAcessManager finish �ɡA
        �R�� _taskQueue �������A�ít�d�o�e�[�W id �� reply signal
        �Y�O�o�{�ӥ��Ȥw�g�����F�A�K�o�e finish
        """
        url = str(reply.url().toString())
        logger.info("NetworkAccessor:_onManagerFinish: %s ����", url)
        
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
        �Q�� url �[�W�@�ǥ��n�� header �����s�������欰�s�@ request 
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

    downloader = Downloader()
    downloader.download(task1)
    downloader.download(task2)

    sys.exit(app.exec_())