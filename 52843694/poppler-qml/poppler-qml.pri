INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/pdfModel.cpp \
    $$PWD/pageImageProvider.cpp

HEADERS += \
    $$PWD/pdfModel.h \
    $$PWD/pageImageProvider.h


unix|win32: LIBS += -lpoppler-qt5
