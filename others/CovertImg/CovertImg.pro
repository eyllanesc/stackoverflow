#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T21:10:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent

TARGET = CovertImg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagewidget.cpp

HEADERS  += mainwindow.h \
    imagewidget.h

FORMS    += mainwindow.ui
