cmake_minimum_required(VERSION 3.0)
project(BrewTroller_Flasher)

include(ExternalProject)

if (WINDOWS)
    set(AVRDUDE_HOST "--host=${COMPILER_PREFIX}")
else()
    set(AVRDUDE_HOST "")
endif ()

ExternalProject_Add(libavrdude
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/avrdude
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/avrdude/configure ${AVRUDE_HOST} --prefix=<INSTALL_DIR>
        BUILD_COMMAND ${MAKE})

ExternalProject_Get_Property(libavrdude install_dir)
include_directories(${install_dir}/include)

add_subdirectory("serial")
include_directories("serial/include")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES flasher_interface.c flasher_interface.h Flasher.cpp Flasher.hpp Scanner.cpp Scanner.hpp Scanner_private.hpp)
add_library(BrewTroller_Flasher SHARED ${SOURCE_FILES})
add_dependencies(BrewTroller_Flasher libavrdude)
target_link_libraries(BrewTroller_Flasher serial ${install_dir}/lib/libavrdude.a)
