#-*- coding: utf-8 -*-
from PySide import QtCore, QtGui, QtUiTools

class MainView(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MainView, self).__init__(parent)
        self.ui = None

        loader = QtUiTools.QUiLoader(self)
        self.ui = loader.load("MainView.ui", self)

        layout = QtGui.QVBoxLayout(self)
        layout.addWidget(self.ui)

