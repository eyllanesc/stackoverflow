#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T11:29:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightScan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lscurve.cpp \
    lsplot.cpp

HEADERS  += mainwindow.h \
    lscurve.h \
    lsplot.h \
    luck.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc

LIBS += -lqwt
INCLUDEPATH += /usr/include/qwt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/C:/Qt/Qt5.7.0/5.7/mingw53_32/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/C:/Qt/Qt5.7.0/5.7/mingw53_32/lib/ -lqwtd

win32:INCLUDEPATH += C:\Qt\Qt5.7.0\5.7\mingw53_32\include\qwt\src

