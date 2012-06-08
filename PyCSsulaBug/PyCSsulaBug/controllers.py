#-*- coding: cp950 -*-

from PyQt4 import QtCore
import handler

class MainController(QtCore.QObject):
    
    updateInfo = QtCore.pyqtSignal(dict)
    updateFinish = QtCore.pyqtSignal()

    downloadInfo = QtCore.pyqtSignal(dict)
    downloadFinish = QtCore.pyqtSignal()
    
    def __init__(self, parent=None):
        super(MainController, self).__init__(parent)
        self._updateHandler = None
        self._downloadHandler = None

        self._setConnection()

    @QtCore.pyqtSlot(handler.UpdateHandler)
    def setUpdateHandler(self, updateHandler):
        self._updateHandler = updateHandler
        self._updateHandler.setParent(self)

    def setDownloadHandler(self, downloadHandler):
        self._downloadHandler = downloadHandler
        self._downloadHandler.setParent(self)

    @QtCore.pyqtSlot(handler.DownloadHandler)    
    def update(self):
        self._updateHandler.update()

    @QtCore.pyqtSlot(str, str)
    def download(self, name, dstDir):
        self._downloadHandler.download(name, dstDir)

    def _setConnection(self):
        self._updateHandler.info.connect(self.updateInfo)
        self._updateHandler.finish.connect(self.udpateFinish)

        self._downloadHandler.info.connect(self.downloadInfo)
        self._downloadHandler.finish.connect(self.downloadFinish)