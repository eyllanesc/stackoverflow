#-------------------------------------------------
#
# Project created by QtCreator 2014-01-06T22:51:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paint
TEMPLATE = app


OTHER_FILES += \
    README.md \
    UNLICENSE.txt

HEADERS += \
    shape.h \
    mainwindow.h \
    drawarea.h \
    command.h \
    floodfill.h

SOURCES += \
    triangle.cpp \
    shape.cpp \
    mainwindow.cpp \
    floodfill.cpp \
    fill.cpp \
    rectangle.cpp \
    pencil.cpp \
    main.cpp \
    ellipse.cpp \
    command.cpp \
    drawarea.cpp
