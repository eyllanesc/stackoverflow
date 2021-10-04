TEMPLATE = app
TARGET = 69432427

QT += qml multimedia

HEADERS += producer.h
SOURCES += main.cpp producer.cpp
RESOURCES += qml.qrc

CONFIG += qmltypes
QML_IMPORT_NAME = com.eyllanesc.multimedia
QML_IMPORT_MAJOR_VERSION = 1
