cmake_minimum_required(VERSION 3.0)

project(QrcRelativePath)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)

# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} main.cpp View.cpp resources.qrc)

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::WebEngineWidgets)
