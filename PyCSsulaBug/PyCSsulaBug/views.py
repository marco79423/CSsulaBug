#-*- coding: utf-8 -*-
from PySide import QtCore, QtGui, QtUiTools

class MainView(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MainView, self).__init__(parent)

        layout = QtGui.QVBoxLayout(self)
      
        loader = QtUiTools.QUiLoader(self)
        layout.addWidget(loader.load("MainView.ui", self))

