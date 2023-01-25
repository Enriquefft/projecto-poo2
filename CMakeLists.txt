find_program(LSB_RELEASE_EXEC lsb_release)
execute_process(
    COMMAND ${LSB_RELEASE_EXEC} -is
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
) # Get linux distro

message(STATUS "Current distro: ${LSB_RELEASE_ID_SHORT}")

cmake_minimum_required(VERSION 3.22)
project(raylib_cpp_example VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_VERSION} VERSION_LESS "3.25.2")
    message(
        STATUS
        "CMake version is less than 3.25.2,
                                                                                        upgrade to silence unnecesary warnings"
    )
endif()

# raylib
message(STATUS "Searching for raylib")
find_package(raylib)
if(NOT raylib_FOUND)
    message(STATUS "raylib not found, downloading...")
    include(FetchContent)
    if(${CMAKE_VERSION} VERSION_LESS "3.25.2")
        fetchcontent_declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.2.0
        )
    else()
        fetchcontent_declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.2.0
            SYSTEM
        )
    endif()
    fetchcontent_makeavailable(raylib)
endif()

# raylib-cpp is not installed as cmake package with aur
if(NOT LSB_RELEASE_ID_SHORT STREQUAL "Arch")
    message(STATUS "Searching for raylib_cpp")
    # raylib_cpp
    find_package(raylib_cpp)
    if(NOT raylib_cpp_FOUND)
        message(STATUS "raylib_cpp not found, downloading...")
        include(FetchContent)
        if(${CMAKE_VERSION} VERSION_LESS "3.25.2")
            fetchcontent_declare(
                raylib_cpp
                GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
                GIT_TAG v4.2.7
            )
        else()
            fetchcontent_declare(
                raylib_cpp
                GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
                GIT_TAG v4.2.7
                SYSTEM
            )
        endif()
        fetchcontent_makeavailable(raylib_cpp)
    endif()
endif()

############### MAIN ###############

# This is the main part:

# set(MODULES "System" "Board" "Utils")
set(MODULES "All")

set(INCLUDE_DIRS "")
set(SOURCES "")

# Recursive source and include
# Only if Sources is empty
if(MODULES STREQUAL "All")
    message(STATUS "Recursively searching for all source files")
    file(GLOB_RECURSE INCLUDE_DIRS "src/*.h*")
    # Test pending
    file(GLOB_RECURSE SOURCES "src/*.cpp")
elseif(SOURCES STREQUAL "")
    message(STATUS "Recursively searching for modules: ${MODULES}")
    foreach(MODULE ${MODULES})
        file(GLOB_RECURSE INCLUDE_DIRS "${INCLUDE_DIRS}" "src/${MODULE}/*.h*")
        file(GLOB_RECURSE SOURCES "${SOURCES}" "src/${MODULE}/*.cpp")
    endforeach()
endif()

# append src/main to SOURCES
list(APPEND SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${INCLUDE_DIRS})

####################################

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(WARNINGS
        -Weverything
        -Wno-string-compare
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
    )
else()
    set(WARNINGS -Wall -Wextra -Wshadow -pedantic)
endif()

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        ${WARNINGS}
        -g
        -fsanitize=address
        -fsanitize=undefined
        -fno-sanitize-recover=all
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE -fsanitize=address -fsanitize=undefined
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
if(LSB_RELEASE_ID_SHORT STREQUAL "Arch")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)
endif()
