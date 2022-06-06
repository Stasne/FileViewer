cmake_minimum_required(VERSION 3.5)

project(FileManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

file(GLOB PROJECT_SOURCES
        src/*.cpp
        src/*.h
        src/mainwindow.ui
        ${TS_FILES}
)

add_executable(FileManager ${PROJECT_SOURCES})

# target_include_directories(${PROJECT_NAME} PRIVATE ui)
target_link_libraries(FileManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
