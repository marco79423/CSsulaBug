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
        url �O�n�U�������}�A�I�s����|�^�Ǹӥ��Ȫ��ѧO�� id
        get �O�M�w�N�n�U�������ȡA��ڪ��U���O�� _startAccess �ާ@
        """
        self._idCount += 1
        newTask = dict(id=self._idCount, urlList=[])

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

        return self._idCount
  
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
    n = NetworkAccessor()
    n.get("http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe")
    n.get(["http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe", "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe"])
    sys.exit(app.exec_())