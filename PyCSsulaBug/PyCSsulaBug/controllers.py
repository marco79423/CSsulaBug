#-*- coding: utf-8 -*-

from PySide import QtCore
import handlers

class MainController(QtCore.QObject):
    
    updateInfo = QtCore.Signal(dict)
    updateFinish = QtCore.Signal()

    downloadInfo = QtCore.Signal(dict)
    downloadFinish = QtCore.Signal()
    
    def __init__(self, parent=None):
        super(MainController, self).__init__(parent)
        self._updateHandler = None
        self._downloadHandler = None

        self._setConnection()

    @QtCore.Slot(handlers.UpdateHandler)
    def setUpdateHandler(self, updateHandler):
        self._updateHandler = updateHandler
        self._updateHandler.setParent(self)

    def setDownloadHandler(self, downloadHandler):
        self._downloadHandler = downloadHandler
        self._downloadHandler.setParent(self)

    @QtCore.Slot(handlers.DownloadHandler)    
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