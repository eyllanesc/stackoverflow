#!/usr/bin/python
# -*- coding: utf-8 -*-

import importlib
import os
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from DialogoImprimir import DialogoImprimir

def iniciar(ruta):
	print(ruta)
	app = QtWidgets.QApplication.instance()
	if app is None:
		app = QtWidgets.QApplication([])
	myapp = DialogoImprimir(ruta)#getPlugins(ruta))
	return myapp.exec_()
