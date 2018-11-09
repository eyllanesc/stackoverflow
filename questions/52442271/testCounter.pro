QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase
QT += widgets
TEMPLATE = app

SOURCES +=  \
    counter.cpp \
    tst_counter.cpp

HEADERS += \
    counter.h
