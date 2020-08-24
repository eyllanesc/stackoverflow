import os
import sys

from PyQt5 import QtCore, QtSql

def create_connections():
    db = QtSql.QSqlDatabase.addDatabase("QMYSQL")
    db.setHostName(os.environ.get("MYSQL_HOST", ""))
    db.setDatabaseName(os.environ.get("MYSQL_DATABASE_NAME", ""))
    db.setUserName(os.environ.get("MYSQL_USERNAME", ""))
    db.setPassword(os.environ.get("MYSQL_PASSWORD", ""))
    if not db.open():
        print(db.lastError().text())
        return False
    query_str = """
CREATE TABLE IF NOT EXISTS contacts (
        contact_id INTEGER PRIMARY KEY,
        first_name TEXT NOT NULL,
        last_name TEXT NOT NULL
);
    """
    query = QtSql.QSqlQuery(query_str)
    if not query.exec_():
        print(query.lastError().text())
    print(db.tables())
    return True


if __name__ == "__main__":
    app = QtCore.QCoreApplication([])
    if not create_connections():
        sys.exit(-1)
