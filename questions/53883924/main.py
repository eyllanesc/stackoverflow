import os
import numpy as np
import pandas as pd
from PyQt5 import QtCore, QtGui, QtWidgets

def pandas_to_str():
    df = pd.DataFrame({ 
        'A' : 1.,
        'B' : pd.Timestamp('20130102'),
        'C' : pd.Series(1,index=list(range(4)),dtype='float32'),
        'D' : np.array([3] * 4,dtype='int32'),
        'E' : pd.Categorical(["test","train","test","train"]),
        'F' : 'foo' })
    return df.to_string(col_space =14,justify = "justify")

if __name__ == '__main__':
    import sys
    dir_path = os.path.dirname(os.path.abspath(__file__))
    app = QtWidgets.QApplication(sys.argv)
    _id = QtGui.QFontDatabase.addApplicationFont(os.path.join(dir_path, "Monospace.ttf"))
    print(_id)
    w = QtWidgets.QTextBrowser()
    w.setStyleSheet('color: blue') 
    w.setFont(QtGui.QFont(QtGui.QFontDatabase.applicationFontFamilies(_id)[0]))
    w.setWordWrapMode(QtGui.QTextOption.NoWrap)
    w.setText(pandas_to_str())
    w.showMaximized()
    sys.exit(app.exec_())