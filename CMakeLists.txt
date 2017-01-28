cmake_minimum_required(VERSION 3.2)
project(btflasher)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DWIN32NATIVE)
endif ()

add_subdirectory(avrdude)
include_directories(avrdude ${CMAKE_CURRENT_BINARY_DIR}/avrdude)

add_subdirectory("serial")
include_directories("serial/include")

include_directories(${CMAKE_JS_INC})
include_directories(node_modules/nan)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Flasher.cpp Flasher.hpp Scanner.cpp Scanner.hpp Flasher_wrap.cpp Flasher_wrap.hpp Scanner_wrap.cpp Scanner_wrap.hpp brewtroller-flasher.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} serial avrdude ${CMAKE_JS_LIB})
