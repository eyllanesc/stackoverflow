QT       += widgets

TARGET = 52583391
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    mattoqimage.h \
    mattoqimage.h

FORMS += \
        mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
