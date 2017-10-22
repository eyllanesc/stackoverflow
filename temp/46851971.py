from random import randint

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *


class Box(QTextBrowser):
    def __init__(self, parent=None):
        QTextBrowser.__init__(self, parent)
        self.setContentsMargins(0, 0, 0, 0)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)

        cstring = """
        QTextBrowser {
            border: 0;
            background-color: #<---->;
            margin: 0px;
            padding-left:0;
            padding-top:0;
            padding-bottom:0;
            padding-right:0;
        }
        """

        ncol = randint(300000, 999999)
        cstring = cstring.replace('<---->', str(ncol))
        self.setStyleSheet(cstring)

        self.document().contentsChange.connect(lambda: self.customGeometry())
        self.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        self.setContentsMargins(0, 0, 0, 0)

    def customGeometry(self):
        if self.isVisible():
            self.setFixedWidth(self.document().idealWidth())
            self.setFixedHeight(self.document().size().height())

    def showEvent(self, event):
        self.customGeometry()
        QTextBrowser.showEvent(self, event)


class MainFrame(QScrollArea):
    def __init__(self, parent=None):
        QScrollArea.__init__(self, parent)
        container = QFrame(self)

        layout = QGridLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)
        self.show()

        text = '''
                <table border="0" cellspacing="0" cellpadding="5" style="background-color: rgba(119, 212, 212, 0.7);">
                <tr>
                    <td width="100">
                        bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla
                    </td>
                <tr>
                <tr>
                   <td>
                        bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla
                    </td>
                <tr>
                </table>
                '''

        for row in range(5):
            for col in range(10):
                box = Box(container)
                box.setText(text)
                box.show()
                layout.addWidget(box, row, col)
        self.setWidget(container)


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    ex = MainFrame()
    ex.show()
    sys.exit(app.exec_())
