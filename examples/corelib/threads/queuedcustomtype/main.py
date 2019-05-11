

from Qt import QtWidgets

from window import Window

if __name__ == "__main__":
    import sys
    sys.path.append('../../../examples')
    print(sys.path)
    app = QtWidgets.QApplication(sys.argv)
    w = Window()
    w.show()
    sys.exit(app.exec_())
