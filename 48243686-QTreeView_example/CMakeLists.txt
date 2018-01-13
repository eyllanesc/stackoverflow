cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(QTreeView_example)

find_package(Qt4 REQUIRED)
INCLUDE         (${QT_USE_FILE})
ADD_DEFINITIONS (${QT_DEFINITIONS})

# Add bin and build dir to include
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

add_subdirectory(src)
