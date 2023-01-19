find_program(LSB_RELEASE_EXEC lsb_release)
execute_process(
    COMMAND ${LSB_RELEASE_EXEC} -is
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

cmake_minimum_required(VERSION 3.24)
project(raylib_cpp_example VERSION 0.1)

# Message current operative system
message(STATUS "Current operative system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Current distro: ${LSB_RELEASE_ID_SHORT}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # raylib
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

# raylib-cpp is not installed as cmake package with aur
if(NOT LSB_RELEASE_ID_SHORT STREQUAL "Arch")
    find_package(raylib_cpp QUIET)
    if(NOT raylib_cpp_FOUND)
        include(FetchContent)
        fetchcontent_declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v4.2.7
        )
        fetchcontent_makeavailable(raylib_cpp)
    endif()
endif()

# # This is the main part:
set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -Weverything
        -Wno-string-compare
        -Wno-c++98-compat
        -Wno-undefined-func-template
)
# -fsanitize=address
# -fsanitize=undefined
# -fno-sanitize-recover=all

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
if(LSB_RELEASE_ID_SHORT STREQUAL "Arch")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)
endif()
