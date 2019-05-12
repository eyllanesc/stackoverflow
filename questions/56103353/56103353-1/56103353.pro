QT += quick
CONFIG += c++11

SOURCES += \
        main.cpp \
        translator.cpp

RESOURCES += qml.qrc


HEADERS += \
    translator.h

TRANSLATIONS = i18n/$${TARGET}_en.ts \
               i18n/$${TARGET}_es.ts

COPY_CONFIG = $$files(i18n/*.qm, true)
copy_cmd.input = COPY_CONFIG
copy_cmd.output = i18n/${QMAKE_FILE_IN_BASE}${QMAKE_FILE_EXT}
copy_cmd.commands = $$QMAKE_COPY_DIR ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_cmd.CONFIG += no_link_no_clean
copy_cmd.variable_out = PRE_TARGETDEPS
QMAKE_EXTRA_COMPILERS += copy_cmd
