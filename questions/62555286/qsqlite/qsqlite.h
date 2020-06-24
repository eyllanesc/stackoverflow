#ifndef QSQLITE_H
#define QSQLITE_H

#include "qsqlite_global.h"

class QSqlDriver;

extern "C" {
    bool QSQLITE_EXPORT enable_extension(QSqlDriver *ptr, bool enabled);
}

#endif // QSQLITE_H
