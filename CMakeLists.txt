
cmake_minimum_required(VERSION 3.25)

project(xfilmee C CXX)

add_executable(xfilmee
    src/main.c
    src/catalog.c
    src/usb_library.cpp
)

set_target_properties(xfilmee PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)

target_compile_options(xfilmee PRIVATE
    -Wall
    -Wextra
)

xsdk_add_xex(xfilmee
    TITLE_ID 0x58464D45
    NAME "XFILMEE"
    VERSION 1.0.0.0
)
