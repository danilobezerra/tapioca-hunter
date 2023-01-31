cmake_minimum_required(VERSION 3.24)
project(ggj_2023 C)

set(HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        $ENV{GDK}/inc
        $ENV{GDK}/res)

set(SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/boot/rom_head.c)

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

add_custom_target(SGDK ALL ${SGDK_COMPILE_COMMAND}
        COMMAND ${PROJECT_COMPILE_COMMAND}
        DEPENDS ${HEADER_FILES}
        SOURCES ${SRC}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ggj_2023 ${SRC})
target_include_directories(ggj_2023 PUBLIC ${HEADER_FILES})
