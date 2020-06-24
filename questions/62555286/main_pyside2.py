from ctypes import CDLL, c_void_p
import os

from PySide2.QtSql import QSqlDatabase, QSqlQuery

import shiboken2

CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))


def load_spatialite():
    queries = (
        "SELECT load_extension('mod_spatialite')",
        "SELECT InitSpatialMetadata(1)",
    )
    q = QSqlQuery()
    for query in queries:
        if not q.exec_(query):
            print(
                f"Error: cannot load the Spatialite extension ({q.lastError().text()})"
            )
            return False
    return True


def main():
    db = QSqlDatabase.addDatabase("QSQLITE")

    db.setDatabaseName("foo.sqlite")
    if not db.open():
        sys.exit(-1)

    lib = CDLL(os.path.join(CURRENT_DIR, "libqsqlite.so"))
    lib.enable_extension(c_void_p(shiboken2.getCppPointer(db.driver())[0]))
    load_spatialite()

    query = QSqlQuery()

    query.exec_("CREATE TABLE my_line(id INTEGER PRIMARY KEY)")
    query.exec_(
        """SELECT AddGeometryColumn("my_line","geom" , 4326, "LINESTRING", 2)"""
    )

    polygon_wkt = "POLYGON ((11 50,11 51,12 51,12 50,11 50))"

    XA = 11
    YA = 52
    XB = 12
    YB = 49

    line_wkt = "LINESTRING({0} {1}, {2} {3})".format(XA, YA, XB, YB)

    query.prepare("""INSERT INTO my_line VALUES (?,GeomFromText(?, 4326))""")

    query.addBindValue(1)
    query.addBindValue(line_wkt)
    query.exec_()

    query.prepare(
        """SELECT astext(st_intersection(geom, GeomFromText(?, 4326))) from my_line WHERE st_intersects(geom, GeomFromText(?, 4326))"""
    )
    query.addBindValue(polygon_wkt)
    query.addBindValue(polygon_wkt)
    query.exec_()

    while query.next():
        for i in range(query.record().count()):
            print(query.value(i))


if __name__ == "__main__":
    main()

