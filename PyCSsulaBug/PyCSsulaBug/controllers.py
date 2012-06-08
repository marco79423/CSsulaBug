#-*- coding: cp950 -*-

from PyQt4 import QtCore
import network

class Controller(QtCore.QObject):

    def __init__(self, handler, parent=None):
        super(Controller, self).__init__(parent)
        self._initialize()

    def setHandler(self, handler):
        self._handler = handler

    def handler(self):
        return self._handler

    def _initialize(self):
        self._handler = None

class MainController(Controller):
    
    downloadInfo = QtCore.pyqtSignal(dict)
    downloadFinish = QtCore.pyqtSignal(dict)
    
    updateInfo = QtCore.pyqtSignal(dict)
    updateFinish = QtCore.pyqtSignal(dict)

    def __init__(self, parent=None):
        super(MainController, self).__init__(parent)
        
    @QtCore.pyqtSlot()    
    def update(self):
        self.handler().update()

    @QtCore.pyqtSlot(str, str)
    def download(self, name, dstDir):
        self.handler().download(name, dstDir)

    def _initialize(self):
        self._updateController = UpdateController(self.handler().updaterHandler(), self)

class UpdateController(Controller):
    
    newItem = QtCore.pyqtSignal(dict)
    finish = QtCore.pyqtSignal()

    def __init__(self, parent=None):
        super(UpdateController, self).__init__(parent)
    
    def update():
        pass

    def _initialize(self):
        pass

class DownloadController(Controller):
    
    def __init__(self, parent=None):
        super(DownloadController, self).__init__(parent)
    
    def download(self, name, dstDir):
        pass

    def _initialize(self):
        pass