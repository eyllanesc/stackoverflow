QT -= gui
QT += sql
CONFIG += c++11 console
CONFIG -= app_bundle


SOURCES += main.cpp

include(3rdParty/sqlite.pri)
