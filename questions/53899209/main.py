import os
from PyQt4 import QtGui, uic
from functools import partial

current_dir = os.path.dirname(os.path.abspath(__file__))
Form, Base = uic.loadUiType(os.path.join(current_dir, "ui/main.ui"))

class MainWidget(Base, Form):
	def __init__(self, parent=None):
		super(self.__class__, self).__init__(parent)
		self.setupUi(self)
		buttons = (self.homebutton, self.statusbutton, self.fanbutton, self.energybutton)
		for i, button in enumerate(buttons):
			button.clicked.connect(partial(self.stackedWidget.setCurrentIndex, i))

if __name__ == '__main__':
	import sys
	app = QtGui.QApplication(sys.argv)
	app.setStyle("fusion")
	w = MainWidget()
	w.show()
	sys.exit(app.exec_())
