
cmake_minimum_required(VERSION 3.25)

project(XFILMEE C)

add_executable(xfilmee
    src/main.c
    src/catalog.c
)

set_target_properties(xfilmee PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)

target_include_directories(xfilmee PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(xfilmee PRIVATE
    -Wall
    -Wextra
    -Werror
)

xsdk_add_xex(xfilmee
    TITLE_ID 0x58464D45
    NAME "XFILMEE"
    VERSION 1.0.0.0
)
