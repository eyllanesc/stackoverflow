import sys
import re
from PyQt5 import QtWidgets, QtGui, QtCore, QtSql

TRACE = True

MY_TABLE = "person"
db = QtSql.QSqlDatabase.addDatabase("QSQLITE")
db.setDatabaseName(":memory:")

modelQuery = QtSql.QSqlQueryModel()
modelTable = QtSql.QSqlRelationalTableModel()

g_hits_count = 0
g_total_count = 0
g_selected_count = 0


def trace(message):
    if TRACE:
        print(message)


def _human_key(key):
    parts = re.split(r"(\d*\.\d+|\d+)", key)
    return tuple(
        (e.swapcase() if i % 2 == 0 else float(e)) for i, e in enumerate(parts)
    )


class dlgDetail(QtWidgets.QDialog):
    def __init__(self, parent, index):
        super(dlgDetail, self).__init__(parent)
        self.setModal(False)
        self.setWindowModality(QtCore.Qt.NonModal)
        self.index = index
        self.parent = self.parent()
        trace(f"dlgDetail was called with cur_row: {index.row()}")

        self.setupUi(self)

        # connect signals
        self.accepted.connect(self.dlgDetail_accepted)
        self.rejected.connect(self.dlgDetail_rejected)
        self.pbNew.clicked.connect(self.on_pbNew_clicked)
        self.pbSave.clicked.connect(self.on_pbSave_clicked)
        self.pbSave.setDefault(True)
        self.pbDel.clicked.connect(self.on_pbDel_clicked)
        self.pbCancel.clicked.connect(self.on_pbCancel_clicked)

        if self.index.isValid():
            record_display = modelTable.record(self.index.row())

            persId = record_display.value("persId")
            lastName = record_display.value("lastName")
            firstName = record_display.value("firstName")
            country = record_display.value("name")

            self.efId.setText(persId)
            self.efLastName.setText(lastName)
            self.efFirstName.setText(firstName)
            self.populate_comboBox(self.cmbCountry, country)
        else:

            modelQuery.setQuery("SELECT IFNULL(MAX(id),0)+1 FROM person")
            self.row_id = modelQuery.data(modelQuery.index(0, 0))

            self.efId.setText("new" + str(self.row_id))
            self.efLastName.setText("new" + str(self.row_id))
            self.efFirstName.setText("new" + str(self.row_id))
            self.populate_comboBox(self.cmbCountry, 0)

        self.show()

    def get_geometry(self):
        return (
            self.geometry().x(),
            self.geometry().y(),
            self.geometry().width(),
            self.geometry().height(),
        )

    def center(self, offset):
        frameGm = self.frameGeometry()
        screen = QtWidgets.QApplication.desktop().screenNumber(
            QtWidgets.QApplication.desktop().cursor().pos()
        )
        centerPoint = QtWidgets.QApplication.desktop().screenGeometry(screen).center()
        frameGm.moveCenter(centerPoint)
        self.move(
            frameGm.topLeft()
            + QtCore.QPoint(frameGm.topLeft().x(), frameGm.topLeft().y() + offset)
        )

    def clear_inputs(self):
        self.efId.setText("new")
        self.efLastName.setText("new")
        self.efFirstName.setText("new")
        self.cmbCountry.setCurrentIndex(0)

    def setupUi(self, parent):
        vBox = QtWidgets.QVBoxLayout(self)

        form = QtWidgets.QFormLayout()

        lblId = QtWidgets.QLabel(self)
        lblId.setText("ID:")
        form.setWidget(0, QtWidgets.QFormLayout.LabelRole, lblId)

        self.efId = QtWidgets.QLineEdit(self)
        form.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.efId)

        lblLastName = QtWidgets.QLabel(self)
        lblLastName.setText("Last Name:")
        form.setWidget(1, QtWidgets.QFormLayout.LabelRole, lblLastName)

        self.efLastName = QtWidgets.QLineEdit(self)
        form.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.efLastName)

        lblFirstName = QtWidgets.QLabel(self)
        lblFirstName.setText("First Name:")
        form.setWidget(2, QtWidgets.QFormLayout.LabelRole, lblFirstName)

        self.efFirstName = QtWidgets.QLineEdit(self)
        form.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.efFirstName)

        lblCountry = QtWidgets.QLabel(self)
        lblCountry.setText("Country:")
        form.setWidget(3, QtWidgets.QFormLayout.LabelRole, lblCountry)

        self.cmbCountry = QtWidgets.QComboBox(self)
        form.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.cmbCountry)

        vBox.addLayout(form)

        # command buttons
        hBox = QtWidgets.QHBoxLayout()

        spacerItem = QtWidgets.QSpacerItem(
            40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum
        )
        hBox.addItem(spacerItem)

        self.pbNew = QtWidgets.QPushButton(self)
        self.pbNew.setText("New")
        hBox.addWidget(self.pbNew)

        self.pbSave = QtWidgets.QPushButton(self)
        self.pbSave.setText("Save")
        hBox.addWidget(self.pbSave)

        self.pbDel = QtWidgets.QPushButton(self)
        self.pbDel.setText("Del")
        hBox.addWidget(self.pbDel)

        self.pbCancel = QtWidgets.QPushButton(self)
        self.pbCancel.setText("Cancel")
        hBox.addWidget(self.pbCancel)

        spacerItem1 = QtWidgets.QSpacerItem(
            40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum
        )
        hBox.addItem(spacerItem1)

        vBox.addLayout(hBox)

    def populate_comboBox(self, comboBox, country):
        model = QtSql.QSqlTableModel()
        model.setTable("country")
        model.select()

        comboBox.setModel(model)
        comboBox.setModelColumn(model.fieldIndex("name"))

        # select the person's set country
        index = comboBox.findText(str(country), QtCore.Qt.MatchFixedString)
        if index >= 0:
            comboBox.setCurrentIndex(index)

    def dlgDetail_accepted(self):
        pass

    def dlgDetail_rejected(self):
        pass

    @QtCore.pyqtSlot()
    def on_pbCancel_clicked(self):
        self.reject()

    @QtCore.pyqtSlot()
    def on_pbSave_clicked(self):
        self.parent.update_record(
            self.index,
            self.efId.text(),
            self.efLastName.text(),
            self.efFirstName.text(),
            self.cmbCountry.currentIndex()
        )

    @QtCore.pyqtSlot()
    def on_pbNew_clicked(self):
        self.accept()
        self.parent.new_record()

    @QtCore.pyqtSlot()
    def on_pbDel_clicked(self):
        # self.parent.del_record()
        self.accept()


class FilterHeader(QtWidgets.QHeaderView):
    filterActivated = QtCore.pyqtSignal()

    def __init__(self, parent):
        super().__init__(QtCore.Qt.Horizontal, parent)
        self._editors = []
        self._padding = 4
        self.setStretchLastSection(True)
        self.setDefaultAlignment(QtCore.Qt.AlignLeft | QtCore.Qt.AlignVCenter)
        self.setSortIndicatorShown(False)
        self.sectionResized.connect(self.adjustPositions)
        parent.horizontalScrollBar().valueChanged.connect(self.adjustPositions)

    def setFilterBoxes(self, count):
        while self._editors:
            editor = self._editors.pop()
            editor.deleteLater()
        for index in range(count):
            editor = QtWidgets.QLineEdit(self.parent())
            editor.setPlaceholderText("Filter")
            editor.setClearButtonEnabled(True)
            editor.textChanged.connect(self.textChanged)

            self._editors.append(editor)
        self.adjustPositions()

    def textChanged(self):
        self.filterActivated.emit()

    def sizeHint(self):
        size = super().sizeHint()
        if self._editors:
            height = self._editors[0].sizeHint().height()
            size.setHeight(size.height() + height + self._padding)
        return size

    def updateGeometries(self):
        if self._editors:
            height = self._editors[0].sizeHint().height()
            self.setViewportMargins(0, 0, 0, height + self._padding)
        else:
            self.setViewportMargins(0, 0, 0, 0)
        super().updateGeometries()
        self.adjustPositions()

    def adjustPositions(self):
        for index, editor in enumerate(self._editors):
            height = editor.sizeHint().height()
            editor.move(
                self.sectionPosition(index) - self.offset() + 2,
                height + (self._padding // 2),
            )
            editor.resize(self.sectionSize(index), height)

    def filterText(self, index):
        if 0 <= index < len(self._editors):
            return self._editors[index].text()
        return ""

    def setFilterText(self, index, text):
        if 0 <= index < len(self._editors):
            self._editors[index].setText(text)

    def clearFilters(self):
        for editor in self._editors:
            editor.clear()


class HumanProxyModel(QtCore.QSortFilterProxyModel):
    def lessThan(self, source_left, source_right):
        data_left = source_left.data()
        data_right = source_right.data()
        return True
        if type(data_left) == type(data_right) == str:
            return _human_key(data_left) < _human_key(data_right)
        return super(HumanProxyModel, self).lessThan(source_left, source_right)

    @property
    def filters(self):
        if not hasattr(self, "_filters"):
            self._filters = []
        return self._filters

    @filters.setter
    def filters(self, filters):
        self._filters = filters
        self.invalidateFilter()

        global g_hits_count
        g_hits_count = self.rowCount()

    def filterAcceptsRow(self, sourceRow, sourceParent):
        for i, text in self.filters:
            if 0 <= i < self.sourceModel().columnCount():
                ix = self.sourceModel().index(sourceRow, i, sourceParent)
                data = ix.data()
                if text not in data:
                    return False

        return True


class winMain(QtWidgets.QMainWindow):
    cur_row = -1
    row_id = -1

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("SqlTableModel Test")
        self.setupUi()
        self.setGeometry(300, 200, 700, 500)

        self.treeView.selectionModel().selectionChanged.connect(
            self.item_selection_changed_slot
        )
        self.treeView.doubleClicked.connect(self.on_treeView_doubleClicked)
        self.center()
        self.show()

    def closeEvent(self, event):
        self.deleteLater()

    def new_record(self):
        dlgDetail(self, QtCore.QPersistentModelIndex())

        self.updateStatus()

    def update_record(self, index, persId, lastName, firstName, country_id):
        if index.isValid():
        	row = index.row()
        	record = modelTable.record(row)
        else:
        	row = modelTable.rowCount()
        	modelTable.insertRow(row)
        	record = modelTable.record()
        record.setValue("persId", persId)
        record.setValue("lastName", lastName)
        record.setValue("firstName", firstName)
        record.setValue("name", country_id)
        modelTable.setRecord(row, record)
        # Update Database
        if modelTable.submitAll():
            trace("success on storing data.")
        else:
            print("error on storing data: ", modelTable.lastError().text())

        if not index.isValid():
            record_display = modelTable.record(0)
            row_id = record_display.value("persId")
            trace(f"   got new_row id from database: {row_id} after save.")
        self.updateStatus()

    def edit_record(self, sourceIdx):

        if len(self.treeView.selectionModel().selectedRows()) > 1:
            reply = QtWidgets.QMessageBox.question(
                self,
                f"Editing multiple records",
                f"Do you want to edit *all* the selected records?\rYes = Edit all records, No = Edit only current recaord",
                QtWidgets.QMessageBox.Yes
                | QtWidgets.QMessageBox.No
                | QtWidgets.QMessageBox.Cancel,
                QtWidgets.QMessageBox.Yes,
            )
            if reply == QtWidgets.QMessageBox.Yes:
                for proxy_index in self.treeView.selectionModel().selectedRows():
                    proxy_model = proxy_index.model()
                    index = proxy_model.mapToSource(proxy_index)
                    p_index = QtCore.QPersistentModelIndex(index)
                    dlgDetail(self, p_index)
                return True
        
        if not sourceIdx:
            sourceIdx = self.treeView.currentIndex()
            if not sourceIdx.isValid():
            	trace("not selection")
            	return False
        # only single selection
        trace("single selection")
        proxy_model = sourceIdx.model()
        index = proxy_model.mapToSource(sourceIdx)
        dlgDetail(self, index)
        self.updateStatus()

    @QtCore.pyqtSlot(QtCore.QModelIndex)
    def on_treeView_doubleClicked(self, index):
        self.edit_record(index)

    def handleFilterActivated(self):
        header = self.treeView.header()
        filters = []
        for i in range(header.count()):
            text = header.filterText(i)
            if text:
                filters.append((i, text))
        proxy = self.treeView.model()
        proxy.filters = filters

        self.updateStatus()

    @QtCore.pyqtSlot()
    def item_selection_changed_slot(self):
        selected = self.treeView.selectionModel()
        indexes = selected.selectedIndexes()

        global g_selected_count
        g_selected_count = len(selected.selectedRows())

        sourceIdx = self.treeView.currentIndex()
        trace(f"sourceIdx.row() -> {sourceIdx.row()}")
        ix = self.treeView.model().index(
            sourceIdx.row(), 0
        )  # column which contains the id

        self.cur_row = sourceIdx.row()
        self.row_id = ix.data()

        trace(f"setting cur_row to -> {self.cur_row}")
        trace(f"setting row_id to -> {self.row_id}")

        record = modelTable.record(self.cur_row)

        persId = record.value("persId")
        lastName = record.value("lastName")
        firstName = record.value("firstName")
        country = record.value("name")

        trace(f"self.cur_row: {self.cur_row}")
        trace(f"self.row_id : {self.row_id}")
        trace(f"persId: {persId}")
        trace(f"lastName: {lastName}")

        self.updateStatus()

    def refresh(self):
        self.clear_all_filters()

        modelTable.select()  # fetch the data of the table into the model

        # self.treeView.sortByColumn(2, QtCore.Qt.DescendingOrder)

        self.updateStatus()

        self.statusBar.showMessage(f"data reloaded.")

    def updateStatus(self):
        global g_hits_count, g_total_count, g_selected_count

        sStatusText = f"Selected: {str(g_selected_count)} / Hits: {str(g_hits_count)} / Total: {str(g_total_count)}      |      Current row: {self.cur_row}, row id: {self.row_id}"

        self.statusBar.showMessage(sStatusText)

    def keyReleaseEvent(self, eventQKeyEvent):
        key = eventQKeyEvent.key()
        modifiers = QtWidgets.QApplication.keyboardModifiers()
        if modifiers == QtCore.Qt.ShiftModifier and key == QtCore.Qt.Key_Escape:
            self.clear_all_filters()

    def keyPressEvent(self, event):
        key = event.key()

        modifiers = QtWidgets.QApplication.keyboardModifiers()

        if modifiers != QtCore.Qt.ShiftModifier:
            focus_obj = self.focusWidget()

            if key == QtCore.Qt.Key_Return:
                if isinstance(focus_obj, QtWidgets.QTreeView):
                    self.edit_record(self.treeView.currentIndex())

            elif key == QtCore.Qt.Key_Escape:
                if isinstance(focus_obj, QtWidgets.QLineEdit):
                    focus_obj.clear()

    def clear_all_filters(self):
        # clear all inputs of type QLineEdit
        lineEdits = self.findChildren(QtWidgets.QLineEdit)
        for lineEdit in lineEdits:
            lineEdit.clear()

    def center(self):
        frameGm = self.frameGeometry()
        screen = QtWidgets.QApplication.desktop().screenNumber(
            QtWidgets.QApplication.desktop().cursor().pos()
        )
        centerPoint = QtWidgets.QApplication.desktop().screenGeometry(screen).center()
        frameGm.moveCenter(centerPoint)
        self.move(frameGm.topLeft())

    def setupUi(self):
        self.centralwidget = QtWidgets.QWidget(self)
        hBox = QtWidgets.QHBoxLayout(self.centralwidget)

        self.treeView = QtWidgets.QTreeView(self.centralwidget)

        self.treeView.setRootIsDecorated(False)
        self.treeView.setSortingEnabled(True)
        self.treeView.setAlternatingRowColors(True)
        self.treeView.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.treeView.setSelectionMode(QtWidgets.QAbstractItemView.ExtendedSelection)
        self.treeView.header().setStretchLastSection(True)

        hBox.addWidget(self.treeView)
        self.setCentralWidget(self.centralwidget)

        header = FilterHeader(self.treeView)
        self.treeView.setHeader(header)
        # self.treeView.sortByColumn(2, QtCore.Qt.DescendingOrder)

        # StatusBar
        self.statusBar = QtWidgets.QStatusBar()
        self.setStatusBar(self.statusBar)

        # ToolBar
        exitAct = QtWidgets.QAction(
            "Exit", self, shortcut="Ctrl+Q", triggered=QtWidgets.qApp.quit
        )
        newRecordAct = QtWidgets.QAction(
            "New", self, shortcut="Ctrl+N", triggered=self.new_record
        )
        editRecordAct = QtWidgets.QAction(
            "Edit", self, shortcut="Return", triggered=self.edit_record
        )
        refreshAct = QtWidgets.QAction(
            "Refresh", self, shortcut="F5", triggered=self.refresh
        )

        self.toolbar = self.addToolBar("Exit")
        self.toolbar.addAction(exitAct)
        self.toolbar.addSeparator()
        self.toolbar.addAction(newRecordAct)
        self.toolbar.addAction(editRecordAct)
        self.toolbar.addSeparator()
        self.toolbar.addAction(refreshAct)

        modelTable.setTable(MY_TABLE)

        modelTable.setHeaderData(0, QtCore.Qt.Horizontal, "row id")
        modelTable.setHeaderData(1, QtCore.Qt.Horizontal, "ID")
        modelTable.setHeaderData(2, QtCore.Qt.Horizontal, "Last Name")
        modelTable.setHeaderData(3, QtCore.Qt.Horizontal, "First Name")
        modelTable.setHeaderData(4, QtCore.Qt.Horizontal, "Country")

        modelTable.setRelation(4, QtSql.QSqlRelation("country", "id", "name"))

        modelTable.setEditStrategy(QtSql.QSqlTableModel.OnManualSubmit)

        self.treeView.setModel(
            modelTable
        )  # display data of the SQLTableModel into the QTreeView
        if not TRACE:
            self.treeView.setColumnHidden(0, True)

        # enable human sorting
        proxy = HumanProxyModel(self)
        proxy.setSourceModel(modelTable)
        self.treeView.setModel(proxy)

        # enable filtering
        header.setFilterBoxes(modelTable.columnCount())
        header.filterActivated.connect(self.handleFilterActivated)

        # update counters
        global g_total_count, g_hits_count
        g_total_count = modelTable.rowCount()
        g_hits_count = g_total_count
        self.updateStatus()


def create_sample_data():
    modelQuery.setQuery(
        """CREATE TABLE IF NOT EXISTS country (                                    
                                    id   INTEGER PRIMARY KEY UNIQUE NOT NULL,
                                    name TEXT
                                    )"""
    )

    modelQuery.setQuery(
        """CREATE TABLE IF NOT EXISTS person (
                                   id         INTEGER PRIMARY KEY UNIQUE NOT NULL,
                                   persId     TEXT,
                                   lastName   TEXT,
                                   firstName  TEXT,
                                   country_id INTEGER NOT NULL DEFAULT 3,
              FOREIGN KEY (country_id) REFERENCES country(id)
                                   )"""
    )

    # create some sample data for our model
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (0, 'None')")
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (1, 'Angola')")
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (2, 'Serbia')")
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (3, 'Georgia')")

    modelQuery.setQuery(
        "INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (1, '1001', 'a', 'Robert', 1)"
    )
    modelQuery.setQuery(
        "INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (2, '1002', 'b', 'Brad', 2)"
    )
    modelQuery.setQuery(
        "INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (3, '1003', 'c', 'Angelina', 3)"
    )


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)

    create_sample_data()

    window = winMain()
    sys.exit(app.exec_())
