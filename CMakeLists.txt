cmake_minimum_required(VERSION 3.14)
project(raylib_cpp_example)

# raylib
find_package(raylib QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    fetchcontent_declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.2.0
    )
    fetchcontent_makeavailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if(NOT raylib_cpp_FOUND)
    include(FetchContent)
    fetchcontent_declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.2.6
    )
    fetchcontent_makeavailable(raylib_cpp)
endif()

# This is the main part:
set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
