cmake_minimum_required(VERSION 3.24)
project(GGJ-2023 C)

set(HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        $ENV{GDK}
        $ENV{GDK}/inc
        $ENV{GDK}/res)

set(SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/boot/rom_head.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/input.c)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(type debug)
ELSE()
    set(type clean release)
ENDIF()

set(SGDK_COMPILE_COMMAND
        $ENV{GDK}/bin/make.exe
        -f $ENV{GDK}/makelib.gen ${type})

set(PROJECT_COMPILE_COMMAND
        $ENV{GDK}/bin/make.exe
        -f $ENV{GDK}/makefile.gen ${type})

add_custom_target(GGJ-2023 ALL ${SGDK_COMPILE_COMMAND}
        COMMAND ${PROJECT_COMPILE_COMMAND}
        DEPENDS ${HEADER_FILES}
        SOURCES ${SRC}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(file-discovery ${SRC})
target_include_directories(file-discovery PUBLIC ${HEADER_FILES})
