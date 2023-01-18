cmake_minimum_required(VERSION 3.24)
project(raylib_cpp_example VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS
    " -Weverything \
-Wno-string-compare -Wno-c++98-compat -Wno-undefined-func-template \
-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
"
)

# raylib
# find_package(raylib)
# if(NOT raylib_FOUND)
include(FetchContent)
fetchcontent_declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.2.0
)
fetchcontent_makeavailable(raylib)
# endif()

# raylib-cpp
# find_library(raylib-cpp /usr/incude/)

# if(NOT raylib-cpp)
find_package(raylib-cpp)
if(NOT raylib_cpp_FOUND)
    include(FetchContent)
    fetchcontent_declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.2.7
    )
    fetchcontent_makeavailable(raylib_cpp)
endif()
# endif()

# This is the main part:
set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
