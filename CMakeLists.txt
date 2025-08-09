#
# Animated 3D Fractals - Interactive Real-Time Fractal Explorer
# 
# Modern CMake build system for a powerful 3D fractal rendering engine
# Features: Real-time exploration, animation system, multiple output formats
#
# Requirements:
#   - CMake 3.16+
#   - C++17 compatible compiler  
#   - OpenGL 3.0+
#   - Git (for submodules)
#
# Build Instructions:
#   mkdir build && cd build
#   cmake ..
#   cmake --build .
#
# Dependencies (included as submodules):
#   - SDL2 2.32.8: Graphics, input, window management
#   - Google Test: Unit testing framework
#

cmake_minimum_required(VERSION 3.16)

project(Animated3DFractals VERSION 1.0.0 LANGUAGES CXX
        DESCRIPTION "Interactive Real-Time 3D Fractal Explorer"
        HOMEPAGE_URL "https://github.com/cschladetsch/Animated-3D-Fractals")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compile options for better debugging and warnings
add_compile_options(-Wall -Wextra -g)

# Find required packages
find_package(OpenGL REQUIRED)

# Add SDL2 from External directory
set(SDL_SHARED OFF CACHE BOOL "Build shared libraries")
set(SDL_STATIC ON CACHE BOOL "Build static libraries")
set(SDL_TEST OFF CACHE BOOL "Build test programs")
add_subdirectory(External/SDL2)

# Set SDL2 variables
set(SDL2_LIBRARIES SDL2-static SDL2main)
set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/External/SDL2/include)
set(BUILD_MAIN_APPS ON)
message(STATUS "Using SDL2 from External/ directory")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/AntTweakBar/include
    ${CMAKE_SOURCE_DIR}/AntTweakBar/src
    ${CMAKE_SOURCE_DIR}/GL
    ${SDL2_INCLUDE_DIRS}
)

# Add preprocessor definitions
add_definitions(
    -DTW_NO_LIB_PRAGMA
    -DTW_STATIC
    -D_UNIX
    -DHAVE_OPENGL
)

# Core library source files
set(CORE_SOURCES
    source/camera.cpp
    source/interpolate.cpp
    source/shader.cpp
    source/uniforms.cpp
)

# AntTweakBar sources
set(ANTTWEAKBAR_SOURCES
    AntTweakBar/src/TwBar.cpp
    AntTweakBar/src/TwFonts.cpp
    AntTweakBar/src/LoadOGL.cpp
    AntTweakBar/src/TwMgr.cpp
    AntTweakBar/src/TwEventSDL.c
    AntTweakBar/src/TwPrecomp.cpp
    AntTweakBar/src/TwColors.cpp
    AntTweakBar/src/TwOpenGL.cpp
    AntTweakBar/src/TwEventSDL12.c
    AntTweakBar/src/TwEventSDL13.c
    AntTweakBar/src/LoadOGLCore.cpp
    AntTweakBar/src/TwOpenGLCore.cpp
    AntTweakBar/src/TwEventSDL20.c
)

# Create core library
add_library(fractal_core STATIC
    ${CORE_SOURCES}
    ${ANTTWEAKBAR_SOURCES}
)

target_link_libraries(fractal_core 
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    m
    X11
)

# Main executable
add_executable(boxplorer2
    source/boxplorer2.cpp
)

# Tiler executable (separate program)
add_executable(tiler
    source/tiler.cpp
)

target_link_libraries(boxplorer2 
    fractal_core
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    m
    X11
)

# Utility executables
add_executable(edit-cfg source/edit-cfg.cpp)
add_executable(shadershrink source/shadershrink.cpp)

add_executable(sdl2-test source/sdl2-test.cpp)
target_link_libraries(sdl2-test 
    ${SDL2_LIBRARIES}
)

# Testing
enable_testing()

# Add Google Test
add_subdirectory(External/googletest)

# Test executable
add_executable(unit_tests
    tests/test_interpolate.cpp
    tests/test_camera.cpp
    tests/test_main.cpp
)

target_link_libraries(unit_tests
    fractal_core
    gtest
    gtest_main
    pthread
)

# Register tests with CTest
add_test(NAME UnitTests COMMAND unit_tests)

# Custom target for running tests
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS unit_tests
)