QT -= gui
QT += remoteobjects
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
    minimalsource.cpp

HEADERS += \
    minimalsource.h

REPC_SOURCE += ../remoteminimal.rep
