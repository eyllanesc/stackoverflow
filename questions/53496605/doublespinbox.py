from PyQt5 import QtCore, QtWidgets

class DoubleSpinBox(QtWidgets.QDoubleSpinBox):
    minimize_signal = QtCore.pyqtSignal()

    def __init__(self, *args, **kwargs):
        super(DoubleSpinBox, self).__init__(*args, **kwargs)
        self.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)

    def contextMenuEvent(self, event):
        QtCore.QTimer.singleShot(0, self.add_actions)
        super(DoubleSpinBox, self).contextMenuEvent(event)

    @QtCore.pyqtSlot()
    def add_actions(self):
        for w in QtWidgets.QApplication.topLevelWidgets():
            if isinstance(w, QtWidgets.QMenu) and w.objectName() == "qt_edit_menu":
                w.addSeparator()
                minimize_action = w.addAction("minimize this parameter")
                minimize_action.triggered.connect(self.minimize_signal)

if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = DoubleSpinBox()
    w.show()
    sys.exit(app.exec_())