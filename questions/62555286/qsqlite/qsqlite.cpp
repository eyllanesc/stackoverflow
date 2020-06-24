#include "qsqlite.h"

#include <sqlite3.h>

#include <QSqlDriver>
#include <QVariant>

bool enable_extension(QSqlDriver *driver, bool enabled)
{
    if(!driver)
        return false;
    QVariant v = driver->handle();
    if (!v.isValid() || !(qstrcmp(v.typeName(), "sqlite3*")==0))
        return false;
    if(sqlite3 *db_handle = *static_cast<sqlite3 **>(v.data())){
        sqlite3_initialize();
        sqlite3_enable_load_extension(db_handle, enabled);
        return true;
    }
    return false;
}
