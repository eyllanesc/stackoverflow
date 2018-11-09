import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *

from Modules.Databases import DatabaseManager


class Tab1(QWidget):
    def __init__(self, parent=None):
        super(Tab1, self).__init__(parent=parent)
        layout = QFormLayout()
        layout.setVerticalSpacing(20)

        h_l = QHBoxLayout()
        h_l.setSpacing(10)
        search_line = QLineEdit()
        search_btn = QPushButton()
        search_btn.setText('Search')
        h_l.addWidget(search_line)
        h_l.addWidget(search_btn)
        layout.addItem(h_l)

        layout.addRow("ID", QTextBrowser())
        layout.addRow("Name", QTextBrowser())
        layout.addRow("Mid-Term", QTextBrowser())
        layout.addRow("Lectures", QTextBrowser())
        layout.addRow("Responding", QTextBrowser())
        layout.addRow("Term - Degrees", QTextBrowser())
        layout.addRow("Final - Exam", QTextBrowser())
        layout.addRow("End - Degrees", QTextBrowser())
        self.setLayout(layout)


class Tab2(QWidget):
    def __init__(self, parent=None):
        super(Tab2, self).__init__(parent=parent)
        layout = QFormLayout()

        self.d_view = QTableWidget(self)

        self.d_view.resizeColumnsToContents()
        self.d_view.resizeRowsToContents()

        self.id1 = QLineEdit()
        self.name = QLineEdit()
        self.term = QLineEdit()
        self.mid = QLineEdit()
        self.lec = QLineEdit()
        self.res = QLineEdit()
        self.final = QLineEdit()
        self.end = QLineEdit()

        self.add_btn = QPushButton()
        self.add_btn.setText("Add New")
        self.add_btn.setFixedSize(100, 50)
        edit_btn = QPushButton()
        edit_btn.setText("Edit Current")
        edit_btn.setFixedSize(100, 50)
        del_btn = QPushButton()
        del_btn.setText("Delete Current")
        del_btn.setFixedSize(100, 50)

        end_less = QLineEdit()
        end_greater = QLineEdit()
        term_less = QLineEdit()
        term_greater = QLineEdit()
        update_btn = QPushButton()
        update_btn.setText("Filter")
        update_btn.setFixedSize(50, 30)

        h_l = QHBoxLayout()
        h_l.setSpacing(10)
        h_l.addWidget(QLabel('ID'))
        h_l.addWidget(self.id1)
        h_l.addWidget(QLabel('Name'))
        h_l.addWidget(self.name)
        h_l.addWidget(QLabel('Term - Degrees'))
        h_l.addWidget(self.term)

        h_l_2 = QHBoxLayout()
        h_l_2.setSpacing(10)
        h_l_2.addWidget(QLabel('Mid - Term'))
        h_l_2.addWidget(self.mid)
        h_l_2.addWidget(QLabel('Lectures'))
        h_l_2.addWidget(self.lec)
        h_l_2.addWidget(QLabel('Results'))
        h_l_2.addWidget(self.res)

        h_l_2.addWidget(QLabel('Final'))
        h_l_2.addWidget(self.final)
        h_l_2.addWidget(QLabel("End - Degrees"))
        h_l_2.addWidget(self.end)

        h_l_3 = QHBoxLayout()
        h_l_3.setSpacing(10)
        h_l_3.addStretch()
        h_l_3.addWidget(self.add_btn)
        h_l_3.addWidget(edit_btn)
        h_l_3.addWidget(del_btn)
        h_l_3.addStretch()

        h_l_4 = QHBoxLayout()
        h_l_4.setSpacing(10)
        h_l_4.addWidget(QLabel('Term <'))
        h_l_4.addWidget(term_less)
        h_l_4.addWidget(QLabel('Term >'))
        h_l_4.addWidget(term_greater)
        h_l_4.addWidget(QLabel('End <'))
        h_l_4.addWidget(end_less)
        h_l_4.addWidget(QLabel('End >'))
        h_l_4.addWidget(end_greater)
        h_l_4.addWidget(update_btn)

        layout.addWidget(self.d_view)
        layout.addItem(h_l)
        layout.addItem(h_l_2)
        layout.addItem(h_l_3)
        layout.addItem(h_l_4)
        self.setLayout(layout)

    def setData(self, headers, datas):
        self.d_view.setColumnCount(len(headers))
        self.d_view.setRowCount(len(datas))

        self.d_view.setHorizontalHeaderLabels(headers)

        for j, data in enumerate(datas):
            for i, d in enumerate(data):
                newitem = QTableWidgetItem("{}".format(d))
                self.d_view.setItem(j, i, newitem)

    def readData(self):
        name = self.name.text()
        mid = self.mid.text()
        lec = self.lec.text()
        res = self.res.text()
        term = self.term.text()
        final = self.final.text()
        end = self.end.text()

        data = (name, mid, lec, res, term, final, end)

        if any(elem is "" for elem in data):
            return
        return data


class Tabs(QTabWidget):
    def __init__(self, parent=None):
        super(Tabs, self).__init__(parent)
        self.dbu = DatabaseManager('students.db', 'degrees')

        self.tab1 = Tab1(self)
        self.tab2 = Tab2(self)

        self.addTab(self.tab1, "Data View")
        self.addTab(self.tab2, "Data Edit")

        self.setWindowTitle("نـظـام إدارة بـيـانـات الـطـلاب")
        self.setFixedSize(800, 400)
        self.setWindowIcon(QIcon('icon.png'))

        self.tab2.add_btn.clicked.connect(self.add)
        self.updateData()

    def add(self):
        data = self.tab2.readData()
        if data:
            self.dbu.addentry(data)
            self.updateData()

    def updateData(self):
        headers = self.dbu.getcols()
        datas = self.dbu.gettable()
        self.tab2.setData(headers=headers, datas=datas)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Tabs()
    ex.show()
    sys.exit(app.exec_())
