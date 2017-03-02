QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    nodes/2d/sprite/csprite2d.h \
    glwidget.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    nodes/2d/sprite/csprite2d.cpp \
    glwidget.cpp

QMAKE_CXXFLAGS += -std=c++11
