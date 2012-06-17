#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import views
import handlers
import models

class MainWindow(QtGui.QMainWindow):
    
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self._mainView = views.MainView(self)
        self._model = models.SiteModel(self)
        self._setConnection()
                
        self.setCentralWidget(self._mainView)
        self._mainView.ui.tableView.setModel(self._model.model())

        self._model.update()
        
    def _setConnection(self):
        pass    

if __name__ in "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)

    m = MainWindow()
    m.show()
    sys.exit(app.exec_())