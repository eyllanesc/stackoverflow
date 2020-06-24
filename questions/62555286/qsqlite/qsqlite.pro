QT -= gui
QT += sql
TEMPLATE = lib
DEFINES += QSQLITE_LIBRARY
CONFIG += unversioned_libname unversioned_soname
CONFIG += c++11
SOURCES += \
    qsqlite.cpp

HEADERS += \
    qsqlite_global.h \
    qsqlite.h

LIBS += -lsqlite3

