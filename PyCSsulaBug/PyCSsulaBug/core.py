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

        self._setConnection()

        #self.update()

    @QtCore.Slot()
    def update(self):
        self._model.update()

    @QtCore.Slot(str, str)
    def download(self, name, dstDir):
        self._downloadHandler.download(name, dstDir)

    @QtCore.Slot()
    def model(self):
        return self._model

    def _setConnection(self):
        self._model.updateInfo.connect(self.updateInfo)
        self._model.updateFinish.connect(self.updateFinish)

        self._downloadHandler.info.connect(self.downloadInfo)
        self._downloadHandler.finish.connect(self.downloadFinish)