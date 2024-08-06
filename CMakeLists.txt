cmake_minimum_required(VERSION 3.28)
project(aLite)

set(ENABLE_ASAN OFF)
if (ENABLE_ASAN)
    message(STATUS "build with ASAN")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(libraries/include)
include_directories(aLiteLib)

file(GLOB_RECURSE LIBRARIES_SRC "libraries/*.c" "libraries/*.cpp")
file(GLOB_RECURSE aLiteLib_SRC "aLiteLib/*.c" "aLiteLib/*.cpp")

add_executable(aLite
        ${LIBRARIES_SRC}
        ${aLiteLib_SRC}
        main.cpp
)


add_library(glfw3 SHARED IMPORTED)
set_target_properties(glfw3 PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libraries/lib/glfw3.dll
        IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/libraries/lib/glfw3dll.lib
)
target_link_libraries(aLite glfw3)
