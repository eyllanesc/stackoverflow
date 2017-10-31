from PyQt5.QtSql import *
from PyQt5.QtWidgets import *


def createConnection():
    db = QSqlDatabase.addDatabase("QSQLITE")
    db.setDatabaseName(":memory:")
    if not db.open():
        QMessageBox.critical(None, "Cannot open database",
                             "Unable to establish a database connection.\n"
                             "This example needs SQLite support. Please read "
                             "the Qt SQL driver documentation for information how "
                             "to build it.\n\n"
                             "Click Cancel to exit.", QMessageBox.Cancel)
        return False
    query = QSqlQuery()
    query.exec_("CREATE TABLE Scene(sceneID INTEGER PRIMARY KEY, title TEXT NOT NULL);")
    query.exec_("CREATE TABLE Character(characterID INTEGER PRIMARY KEY, fullName TEXT NOT NULL);")
    query.exec_("""CREATE TABLE CharacterInScene(
    characterID INTEGER,
    sceneID INTEGER,
    PRIMARY KEY(characterID, sceneID),
    FOREIGN KEY(characterID) REFERENCES Character(characterID),
    FOREIGN KEY(sceneID) REFERENCES Scene(sceneID));""")

    query.exec_("""INSERT INTO Scene VALUES (1, "Police Station");""")
    query.exec_("""INSERT INTO Scene VALUES (2, "Scene2");""")
    query.exec_("""INSERT INTO Scene VALUES (3, "Scene3");""")

    query.exec_("""INSERT INTO Character VALUES (1, "Harrison Ford");""")
    query.exec_("""INSERT INTO Character VALUES (2, "Rutger Hauer");""")
    query.exec_("""INSERT INTO Character VALUES (3, "Johnny Depp");""")
    query.exec_("""INSERT INTO Character VALUES (4, "Tom Hanks");""")

    query.exec_("""INSERT INTO CharacterInScene VALUES (1, 1);""")

    return True
