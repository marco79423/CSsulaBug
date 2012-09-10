#-*- config: utf-8 -*-

from PySide import QtCore
import handlers
import models

class Core(QtCore.QObject):

    updateInfo = QtCore.Signal(dict)
    updateFinish = QtCore.Signal()

    downloadInfo = QtCore.Signal(dict)
    downloadFinish = QtCore.Signal()

    def __init__(self, parent=None):
        super(Core, self).__init__(parent)
        self._model = models.ComicModel(self)
        self._downloadHandler = handlers.SFDownloadHandler(self)

        self._finishSize = 0
        self._setConnection()

    @QtCore.Slot()
    def update(self):
        self._model.update()

    @QtCore.Slot(str, str)
    def download(self, key, dstDir):
        self._finishSize = 0
        self._downloadHandler.download(str(key), dstDir)

    @QtCore.Slot()
    def progress(self):
        return float(self._finishSize) / self._downloadHandler.taskSize() * 100

    @QtCore.Slot()
    def model(self):
        return self._model

    @QtCore.Slot(dict)
    def _onDownloadInfo(self, info):
        self._finishSize += 1
        self.downloadInfo.emit(info)

    def _setConnection(self):
        self._model.updateInfo.connect(self.updateInfo)
        self._model.updateFinish.connect(self.updateFinish)

        #self._downloadHandler.info.connect(self.downloadInfo)
        self._downloadHandler.info.connect(self._onDownloadInfo)
        self._downloadHandler.finish.connect(self.downloadFinish)