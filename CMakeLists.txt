
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

# Main application
qt_add_executable(FileSuite
    app/main.cpp

    src/core/filesystem/FileEntry.cpp
    src/core/filesystem/DirectoryScanner.cpp

    src/features/organizer/OrganizerRules.cpp
    src/features/organizer/OrganizerPlanBuilder.cpp
    src/features/organizer/OrganizerPlan.cpp
)

target_include_directories(FileSuite
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(FileSuite
    PRIVATE
        Qt6::Widgets
)

# Directory scanner tests
add_executable(ScannerTest
    tests/DirectoryScannerTest.cpp

    src/core/filesystem/FileEntry.cpp
    src/core/filesystem/DirectoryScanner.cpp
)

target_include_directories(ScannerTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Organizer rules tests
add_executable(OrganizerRulesTest
    tests/OrganizerRulesTest.cpp

    src/core/filesystem/FileEntry.cpp
    src/features/organizer/OrganizerRules.cpp
)

target_include_directories(OrganizerRulesTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(OrganizerPlanBuilderTest
    tests/OrganizerPlanBuilderTest.cpp

    src/core/filesystem/FileEntry.cpp
    src/core/filesystem/DirectoryScanner.cpp

    src/features/organizer/OrganizerRules.cpp
    src/features/organizer/OrganizerPlanBuilder.cpp
    src/features/organizer/OrganizerPlan.cpp
)

target_include_directories(OrganizerPlanBuilderTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)