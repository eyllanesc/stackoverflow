#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

#include <sqlite3.h>

int localeCompare(void *, int len1, const void *data1, int len2, const void* data2)
{
    auto qstr1 = QString::fromUtf8(reinterpret_cast<const char*>(data1), len1 * 4);
    auto qstr2 = QString::fromUtf8(reinterpret_cast<const char*>(data2), len2 * 4);

    int end = 0;
    while (qstr1[end] != '\0') {end++;}
    qstr1.truncate(end + 1);

    end = 0;
    while (qstr2[end] != '\0') {end++;}
    qstr2.truncate(end + 1);

    return QString::compare(qstr1, qstr2, Qt::CaseInsensitive);
}

bool create_collate(QSqlDatabase db)
{
    QVariant v = db.driver()->handle();
    if (!v.isValid() || qstrcmp(v.typeName(), "sqlite3*") != 0)
        return -1;

    sqlite3* sql_db = *static_cast<sqlite3* const*>(v.data());
    if (!sql_db)
        return false;

    sqlite3_initialize();
    return sqlite3_create_collation(sql_db, "NOACCENTS", SQLITE_UTF8, NULL, &localeCompare) == SQLITE_OK;
}
int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if(!db.open())
        return -1;
    QSqlQuery q;
    if(!q.exec("SELECT sqlite_version()")){
        qDebug() << q.lastError().text();
        return -1;
    }
    if(q.first()){
        qDebug() << q.value(0).toString();
    }
    if(!create_collate(db))
        return -1;
    if(!q.exec("CREATE TABLE test(x)")){
        qDebug() << q.lastError().text();
        return -1;
    }
    q.prepare("INSERT into test(x) values (?)");
    for(const QString & word: {"z", "a", "p"}){
        q.addBindValue(word);
        if(!q.exec()){
            qDebug() << q.lastError().text();
            return -1;
        }
    }
    if(!q.exec("SELECT x FROM test ORDER BY x COLLATE NOACCENTS")){
        qDebug() << q.lastError().text();
        return -1;
    }
    while (q.next()) {
        qDebug() << q.value(0).toString();
    }

    return 0;
}
