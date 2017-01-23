cmake_minimum_required(VERSION 3.2)
project(btflasher)

include(ExternalProject)

if (WINDOWS)
    set(AVRDUDE_HOST "--host=${COMPILER_PREFIX}")
else()
    set(AVRDUDE_HOST "")
endif ()

ExternalProject_Add(libavrdude
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/avrdude
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/avrdude/configure ${AVRUDE_HOST} --prefix=<INSTALL_DIR>
        BUILD_COMMAND ${MAKE}
        BUILD_BYPRODUCTS <INSTALL_DIR>/lib/libavrdude.a)

ExternalProject_Get_Property(libavrdude install_dir)
ExternalProject_Get_Property(libavrdude binary_dir)
include_directories(${install_dir}/include)
include_directories(${binary_dir})

add_subdirectory("serial")
include_directories("serial/include")

include_directories(${CMAKE_JS_INC})
include_directories(node_modules/nan)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Flasher.cpp Flasher.hpp Scanner.cpp Scanner.hpp Flasher_wrap.cpp Flasher_wrap.hpp Scanner_wrap.cpp Scanner_wrap.hpp brewtroller-flasher.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
add_dependencies(${PROJECT_NAME} libavrdude)
target_link_libraries(${PROJECT_NAME} serial ${install_dir}/lib/libavrdude.a ${CMAKE_JS_LIB})
