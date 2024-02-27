project(qpulsedevicelistfetcher)
cmake_minimum_required(VERSION 3.5.0)

find_library(
    PULSE_LIBRARY
    NAMES
        pulse
)
find_package(
    Qt5
    COMPONENTS
        Widgets
    REQUIRED
)

set(CMAKE_AUTOMOC ON)
set(MOCUIC_DIR ${CMAKE_CURRENT_BINARY_DIR}/.mocuic)

add_executable(
    qpulsedevicelistfetcher
        demo/demo.cpp
        src/qpulsedevicelistfetcher.cpp
)

target_include_directories(
    qpulsedevicelistfetcher
    PRIVATE
        src/
)

set_target_properties(
    qpulsedevicelistfetcher
    PROPERTIES
        AUTOGEN_BUILD_DIR
            ${MOCUIC_DIR}
)

target_link_libraries(
    qpulsedevicelistfetcher
        pulse
        Qt5::Widgets
)
