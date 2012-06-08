#-*- coding: cp950 -*-

from PyQt4 import QtCore
import handler

class MainController(QtCore.QObject):
    
    updateInfo = QtCore.pyqtSignal(dict)
    updateFinish = QtCore.pyqtSignal(dict)

    downloadInfo = QtCore.pyqtSignal(dict)
    downloadFinish = QtCore.pyqtSignal(dict)
    
    def __init__(self, parent=None):
        super(MainController, self).__init__(parent)
        self._updateHandler = None
        self._downloadHandler = None

        self._setConnection()

    @QtCore.pyqtSlot(handler.UpdateHandler)
    def setUpdateHandler(self, updateHandler):
        self._updateHandler = updateHandler

    def setDownloadHandler(self, downloadHandler):
        self._downloadHandler = downloadHandler

    @QtCore.pyqtSlot(handler.DownloadHandler)    
    def update(self):
        self._updateHandler.update()

    @QtCore.pyqtSlot(str, str)
    def download(self, name, dstDir):
        self._downloadHandler.download(name, dstDir)

    def _setConnection(self):
        self._updateHandler.updateInfo.connect(self.updateInfo)
        self._updateHandler.updateFinish.connect(self.udpateFinish)

        self._downloadHandler.downloadInfo.connect(self.downloadInfo)
        self._downloadHandler.downloadFinish.connect(self.downloadFinish)