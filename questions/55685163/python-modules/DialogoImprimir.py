from PyQt5 import QtWidgets

class DialogoImprimir(QtWidgets.QDialog):
    def __init__(self, datos, parent=None):
    	super(DialogoImprimir, self).__init__(parent)
    	self. datos = datos
    	print(self.datos)
