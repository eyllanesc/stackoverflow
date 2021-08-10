TEMPLATE        = lib
CONFIG         += plugin
QT             += core
INCLUDEPATH    += ../app
HEADERS         = fooplugin.h
SOURCES         = fooplugin.cpp
TARGET          = $$qtLibraryTarget(fooplugin)
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = fooplugin.json

CONFIG += install_ok  # Do not cargo-cult this!
