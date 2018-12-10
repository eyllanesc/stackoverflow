CONFIG += warn_on qmltestcase

TEMPLATE = app

DISTFILES += \
    tst_qmltest.qml \
    MouseQml.qml

SOURCES += \
    main.cpp \
    mousememory.cpp

HEADERS += \
    mousememory.h
