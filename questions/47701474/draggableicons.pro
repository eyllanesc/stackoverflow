QT += widgets opengl

HEADERS     = dragwidget.h \
    glwidget.h
RESOURCES   = draggableicons.qrc
SOURCES     = dragwidget.cpp \
              main.cpp \
    glwidget.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/draganddrop/draggableicons
INSTALLS += target

LIBS += -lGLU
