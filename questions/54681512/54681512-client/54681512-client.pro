QT -= gui
QT += remoteobjects

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
    objects.cpp

HEADERS += objects.h

REPC_REPLICA += ../remoteminimal.rep
