QT += quick
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp
RESOURCES += qml.qrc

INCLUDEPATH += /usr/include/oscpack
LIBS += -loscpack 
include($$PWD/3rdPartyLibs/qml-osc/osc.pri)
