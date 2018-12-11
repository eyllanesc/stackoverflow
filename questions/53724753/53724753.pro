QT += quick

TARGET = AppTranslations
SOURCES += \
        main.cpp \
    translator.cpp
HEADERS += \
    translator.h
RESOURCES += qml.qrc

TRANSLATIONS = translations/Lang-en.ts \
               translations/Lang-es.ts \
               translations/Lang-de.ts

