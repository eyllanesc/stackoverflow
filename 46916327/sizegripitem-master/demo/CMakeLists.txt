INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(sizegripitemdemo_SOURCES ../SizeGripItem.cpp MainWindow.cpp main.cpp)
SET(sizegripitemdemo_HEADERS MainWindow.h)
SET(sizegripitemdemo_FORMS MainWindow.ui)

QT4_WRAP_CPP(sizegripitemdemo_HEADERS_MOC ${sizegripitemdemo_HEADERS})
QT4_WRAP_UI(sizegripitemdemo_FORMS_HEADERS ${sizegripitemdemo_FORMS})

ADD_EXECUTABLE(sizegripitemdemo
  ${sizegripitemdemo_SOURCES}
  ${sizegripitemdemo_HEADERS_MOC}
  ${sizegripitemdemo_FORMS_HEADERS})

TARGET_LINK_LIBRARIES(sizegripitemdemo ${QT_LIBRARIES})