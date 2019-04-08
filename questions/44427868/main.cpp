#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlResult>

#include <sqlite3.h>

int enable_spatialite(QSqlDatabase db) {

  QVariant v = db.driver()->handle();

  if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*") == 0) {

    sqlite3 *db_handle = *static_cast<sqlite3 **>(v.data());

    if (db_handle != 0) {

      sqlite3_initialize();

      sqlite3_enable_load_extension(db_handle, 1);

      QSqlQuery query;

      query.exec("SELECT load_extension('mod_spatialite')");

      if (query.lastError().isValid()) {
        qDebug() << "Error: cannot load the Spatialite extension ("
                 << query.lastError().text() << ")";
        return 0;
      }

      qDebug() << "**** SpatiaLite loaded as an extension ***";

      query.exec("SELECT InitSpatialMetadata(1)");

      if (query.lastError().isValid()) {
        qDebug() << "Error: cannot load the Spatialite extension ("
                 << query.lastError().text() << ")";
        return 0;
      }
      qDebug() << "**** InitSpatialMetadata successful ***";

      return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName("memory.db");
  if (!db.open()) {
    qDebug() << "not open";
  }

  qDebug() << enable_spatialite(db);

  QSqlQuery query;

  qDebug() << query.exec(
      "CREATE TABLE test_geom (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
      "name TEXT NOT NULL, measured_value DOUBLE NOT NULL);");
  qDebug() << query.exec("SELECT AddGeometryColumn('test_geom', 'the_geom', "
                         "4326, 'POINT', 'XY');");

  for (int i = 0; i < 10; i++) {
    QString q =
        QString(
            "INSERT INTO test_geom(id, name, measured_value, the_geom) VALUES "
            "(%1,'point %2', %3, GeomFromText('POINT(1.01 2.02)', 4326))")
            .arg("NULL")
            .arg(i)
            .arg(i);
    query.prepare(q);
    qDebug() << i << query.exec();
  }

  qDebug() << query.exec(
      "SELECT id, name, measured_value,  AsText(the_geom), "
      "ST_GeometryType(the_geom), ST_Srid(the_geom) FROM test_geom");

  while (query.next()) {
    QString str;
    for (int i = 0; i < query.record().count(); i++)
      str += query.value(i).toString() + " ";
    qDebug() << str;
  }
  return a.exec();
}
