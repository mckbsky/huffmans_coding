cmake_minimum_required(VERSION 3.8)
project(huffmans_coding)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

include_directories(./src)
include_directories(./headers)
include_directories(/usr/include/qt)
link_directories(/usr/lib/qt)

file(
        GLOB
        SOURCE_FILES
        src/*
        headers/*
)

add_executable(huffmans_coding ${SOURCE_FILES})
target_link_libraries(huffmans_coding Qt5::Widgets)

set(COMPILE_FLAGS "-lm -O2 -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")