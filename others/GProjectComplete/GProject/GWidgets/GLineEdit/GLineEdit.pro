#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T15:18:37
#
#-------------------------------------------------

QT       += widgets

TARGET = GLineEdit
TEMPLATE = lib

DEFINES += GLINEEDIT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        $$PWD/src/glineedit.cpp \
    $$PWD/src/focuslabel.cpp \
    $$PWD/src/focuslineedit.cpp

HEADERS += \
        $$PWD/include/glineedit.h \
    $$PWD/include/focuslabel.h \
    $$PWD/include/focuslineedit.h \
    $$PWD/include/glineedit_global.h

INCLUDEPATH += $$PWD/include

unix {
    target.path = /usr/lib/
    INSTALLS += target
}

DESTDIR = $$PWD/lib
