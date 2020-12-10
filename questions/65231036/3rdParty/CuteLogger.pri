INCLUDEPATH += $$PWD/CuteLogger/include

SOURCES += $$PWD/CuteLogger/src/Logger.cpp \
           $$PWD/CuteLogger/src/AbstractAppender.cpp \
           $$PWD/CuteLogger/src/AbstractStringAppender.cpp \
           $$PWD/CuteLogger/src/ConsoleAppender.cpp \
           $$PWD/CuteLogger/src/FileAppender.cpp \
           $$PWD/CuteLogger/src/RollingFileAppender.cpp

HEADERS += $$PWD/CuteLogger/include/Logger.h \
           $$PWD/CuteLogger/include/CuteLogger_global.h \
           $$PWD/CuteLogger/include/AbstractAppender.h \
           $$PWD/CuteLogger/include/AbstractStringAppender.h \
           $$PWD/CuteLogger/include/ConsoleAppender.h \
           $$PWD/CuteLogger/include/FileAppender.h \
           $$PWD/CuteLogger/include/RollingFileAppender.h

win32 {
    SOURCES += $$PWD/CuteLogger/src/OutputDebugAppender.cpp
    HEADERS += $$PWD/CuteLogger/include/OutputDebugAppender.h
}

android {
    SOURCES += $$PWD/CuteLogger/src/AndroidAppender.cpp
    HEADERS += $$PWD/CuteLogger/include/AndroidAppender.h
}
