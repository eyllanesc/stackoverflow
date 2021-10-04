cmake_minimum_required(VERSION 3.14)

project(69432427 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)

set(PROJECT_SOURCES
  main.cpp
  producer.cpp
  qml.qrc
  )


add_executable(69432427
  ${PROJECT_SOURCES}
  )

qt6_add_qml_module(69432427
  URI com.eyllanesc.multimedia
  VERSION 1.0
)

target_compile_definitions(69432427
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(69432427
  PRIVATE Qt6::Core Qt6::Quick Qt6::Multimedia)
