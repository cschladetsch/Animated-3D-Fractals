cmake_minimum_required(VERSION 3.16)

project(Animated3DFractals VERSION 1.0.0 LANGUAGES CXX)

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
find_package(PkgConfig REQUIRED)

# Find SDL2 (optional for unit tests)
pkg_check_modules(SDL2 sdl2)
if(SDL2_FOUND)
    find_package(OpenGL REQUIRED)
    set(BUILD_MAIN_APPS ON)
    message(STATUS "SDL2 found - building main applications")
else()
    set(BUILD_MAIN_APPS OFF)
    message(STATUS "SDL2 not found - building only unit tests")
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

if(BUILD_MAIN_APPS)
    include_directories(
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
endif()

# Core library source files (minimal for testing)
set(CORE_SOURCES
    source/camera.cpp
    source/interpolate.cpp
)

# Create minimal core library for testing
add_library(fractal_core STATIC
    ${CORE_SOURCES}
)

if(BUILD_MAIN_APPS)
    # Extended sources for main applications
    set(EXTENDED_SOURCES
        source/shader.cpp
        source/uniforms.cpp
        source/glsl.cpp
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
    
    # Extended core library for main applications
    add_library(fractal_core_extended STATIC
        ${CORE_SOURCES}
        ${EXTENDED_SOURCES}
        ${ANTTWEAKBAR_SOURCES}
    )
    
    target_link_libraries(fractal_core_extended 
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
        m
        X11
    )
    
    # Main executable
    add_executable(boxplorer2
        source/boxplorer2.cpp
        source/tiler.cpp
        source/oculus_sdk2.cpp
        source/oculus_sdk4.cpp
    )
    
    target_link_libraries(boxplorer2 
        fractal_core_extended
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
        m
        X11
    )
    
    # Utility executables
    add_executable(edit-cfg source/edit-cfg.cpp)
    add_executable(shadershrink source/shadershrink.cpp)
    add_executable(glsl source/glsl.cpp)
    target_link_libraries(glsl fractal_core_extended)
    
    add_executable(sdl2-test source/sdl2-test.cpp)
    target_link_libraries(sdl2-test 
        ${SDL2_LIBRARIES}
    )
endif()

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