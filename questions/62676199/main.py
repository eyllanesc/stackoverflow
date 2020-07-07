from PySide2 import QtCore, QtSql
plugin_path = QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.PluginsPath)
print(plugin_path)
print(QtSql.QSqlDatabase.drivers())