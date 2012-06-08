#-*- coding: cp950 -*-

from PyQt4 import QtCore


class UpdateHandler(QtCore.QObject):

    updateInfo = QtCore.pyqtSignal(dict)
    updateFinish = QtCore.pyqtSignal()

    def update(self):
        pass

class DownloadHandler(QtCore.QObject):

    downloadInfo = QtCore.pyqtSignal(dict)
    downloadFinish = QtCore.pyqtSignal(dict)

    def download(self, name, dstDir):
        pass
