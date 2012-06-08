#-*- coding: cp950 -*-

from PyQt4 import QtCore

class Handler(QtCore.QObject):
    pass

class UpdateHandler(Handler):

    updateInfo = QtCore.pyqtSignal(dict)
    updateFinish = QtCore.pyqtSignal(dict)

    def update(self):
        pass

class DownloadHandler(Handler):

    downloadInfo = QtCore.pyqtSignal(dict)
    downloadFinish = QtCore.pyqtSignal(dict)

    def download(self, name, dstDir):
        pass
