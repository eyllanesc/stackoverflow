QT       += widgets

TARGET = 55685163
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pythonutils.cpp

HEADERS += \
        mainwindow.h \
    pythonutils.h

LIBS += -lpython3.7m
INCLUDEPATH += /usr/include/python3.7m
DEPENDPATH += /usr/include/python3.7m

CONFIG += no_keywords

COPY_CONFIG = python-modules
copy_cmd.input = COPY_CONFIG
copy_cmd.output = ${QMAKE_FILE_IN_BASE}${QMAKE_FILE_EXT}
copy_cmd.commands = $$QMAKE_COPY_DIR ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_cmd.CONFIG += no_link_no_clean
copy_cmd.variable_out = PRE_TARGETDEPS
QMAKE_EXTRA_COMPILERS += copy_cmd

DISTFILES += \
    python-modules/DialogoImprimir.py \
    python-modules/plugin_loader.py
