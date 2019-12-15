QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
TARGET = qt_host
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp \
    nativemessenger.cpp
HEADERS += nativemessenger.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    org.eyllanesc.qt_listener.json

