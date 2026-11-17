
cmake_minimum_required(VERSION 3.16)

project(XFILMEE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(XFILMEE
    src/main.cpp
    src/catalog.cpp
    src/controller.cpp
)

target_include_directories(XFILMEE PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
