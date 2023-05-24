project(qpulsedevicelistfetcher)
cmake_minimum_required(VERSION 3.0.0)

include(FindPkgConfig)

find_package(
    Qt5
    REQUIRED
        Widgets
)

find_library(
    PULSE_LIBRARY
    NAMES
        pulse
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(MOCUIC_DIR ${CMAKE_CURRENT_BINARY_DIR}/.mocuic)
set(QPULSEDEVICELISTFETCHER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_executable(
    qpulsedevicelistfetcher
        src/main.cpp
        src/qpulsedevicelistfetcher.cpp
)

set_target_properties(
    qpulsedevicelistfetcher
    PROPERTIES
        AUTOGEN_BUILD_DIR
            ${MOCUIC_DIR}
        RUNTIME_OUTPUT_DIRECTORY
            ${QPULSEDEVICELISTFETCHER_BINARY_DIR}
)

target_link_libraries(
    qpulsedevicelistfetcher
        pulse
        Qt5::Widgets
)
