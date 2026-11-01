
cmake_minimum_required(VERSION 3.21)

project(FileSuite
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.12 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(FileSuite
    app/main.cpp
)

target_link_libraries(FileSuite
    PRIVATE Qt6::Widgets
)
