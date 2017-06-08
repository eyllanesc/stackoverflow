#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlResult>
#include <QDebug>

#include <sqlite3.h>


int enable_spatialite(){
    QSqlDatabase db = QSqlDatabase::database();
    QVariant v = db.driver()->handle();

    char sql[2048];
    int ret;
    char *err_msg = NULL;
    char **results;
    int rows;
    int columns;


    if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*")==0)
    {
        // v.data() returns a pointer to the handle

        sqlite3 *db_handle = *static_cast<sqlite3 **>(v.data());

        if (db_handle != 0) {

            sqlite3_enable_load_extension (db_handle, 1);
            strcpy (sql, "SELECT load_extension('mod_spatialite')");
            ret = sqlite3_exec (db_handle, sql, NULL, NULL, &err_msg);
            if (ret != SQLITE_OK)
            {
                fprintf (stderr, "load_extension() error: %s\n", err_msg);
                sqlite3_free (err_msg);
                return 0;
            }
            fprintf(stderr, "\n\n**** SpatiaLite loaded as an extension ***\n\n");


            strcpy (sql, "SELECT sqlite_version()");
            ret =
                    sqlite3_get_table (db_handle, sql, &results, &rows, &columns, &err_msg);
            if (ret != SQLITE_OK)
            {
                fprintf (stderr, "Error: %s\n", err_msg);
                sqlite3_free (err_msg);
                return 0;
            }
            if (rows < 1)
            {
                fprintf (stderr,"Unexpected error: sqlite_version() not found ??????\n");
                return 0;
            }
            else
            {
                for (int i = 1; i <= rows; i++)
                {
                    fprintf (stderr, "SQLite version: %s\n",
                             results[(i * columns) + 0]);
                }
            }
            sqlite3_free_table (results);
            strcpy (sql, "SELECT spatialite_version()");
            ret =
                    sqlite3_get_table (db_handle, sql, &results, &rows, &columns, &err_msg);
            if (ret != SQLITE_OK)
            {
                fprintf (stderr, "Error: %s\n", err_msg);
                sqlite3_free (err_msg);
                return 0;
            }
            if (rows < 1)
            {
                fprintf (stderr,"Unexpected error: spatialite_version() not found ??????\n");
                return 0;
            }
            else
            {
                for (int i = 1; i <= rows; i++)
                {
                    fprintf (stderr, "SpatiaLite version: %s\n",
                             results[(i * columns) + 0]);
                }
            }
            sqlite3_free_table (results);

            /* initializing SpatiaLite's metadata tables */
            strcpy (sql, "SELECT InitSpatialMetadata(1)");
            ret = sqlite3_exec (db_handle, sql, NULL, NULL, &err_msg);
            if (ret != SQLITE_OK)
            {
                fprintf (stderr, "InitSpatialMetadata() error: %s\n", err_msg);
                sqlite3_free (err_msg);
                return 0;
            }

        }
    }
    return 1;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("memory.db");
    if (!db.open()) {
        qDebug()<<"not open";
    }

    if(enable_spatialite()==1)

        qDebug()<<"successful";
    else
        qDebug()<<"error";

    QSqlQuery query;

    qDebug()<<query.exec("CREATE TABLE test_geom (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, measured_value DOUBLE NOT NULL);");
    qDebug()<<query.exec("SELECT AddGeometryColumn('test_geom', 'the_geom', 4326, 'POINT', 'XY');");



    for(int i=0; i< 10; i++){
        QString q = QString("INSERT INTO test_geom(id, name, measured_value, the_geom) VALUES (%1,'point %2', %3, GeomFromText('POINT(1.01 2.02)', 4326))")
                .arg("NULL").arg(i).arg(i);
        query.prepare(q);
        qDebug()<< i<<query.exec();
    }

    qDebug()<<query.exec("SELECT id, name, measured_value,  AsText(the_geom), ST_GeometryType(the_geom), ST_Srid(the_geom) FROM test_geom");


    while (query.next()) {
        QString str;
        for(int i=0; i < query.record().count(); i++)
            str += query.value(i).toString() + " ";
        qDebug()<<str;
    }
    return a.exec();
}
