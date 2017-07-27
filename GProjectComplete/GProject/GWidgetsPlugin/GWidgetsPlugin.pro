#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T15:26:08
#
#-------------------------------------------------

CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(gwidgetsplugin)
TEMPLATE    = lib


LIBS        += -L.

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

HEADERS += \
    gwidgets.h \
    glineeditplugin.h \
    glineeditmenufactory.h \
    glineeditdialog.h

SOURCES += \
    gwidgets.cpp \
    glineeditplugin.cpp \
    glineeditmenufactory.cpp \
    glineeditdialog.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GWidgets/GLineEdit/lib/release/ -lGLineEdit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GWidgets/GLineEdit/lib/debug/ -lGLineEdit
else:unix: LIBS += -L$$PWD/../GWidgets/GLineEdit/lib/ -lGLineEdit

INCLUDEPATH += $$PWD/../GWidgets/GLineEdit/include
DEPENDPATH += $$PWD/../GWidgets/GLineEdit/include
