#################################################################################
#                          SDL helper lib                                       #
#################################################################################

cmake_minimum_required(VERSION 3.13)

project(sdl DESCRIPTION "SDL Helper")

# C/C++ flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Toolchain
if(NOT DEFINED TARGET)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(TARGET "clang")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(TARGET "gcc")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(TARGET "msvc")
    else()
        message(FATAL_ERROR "Unknown target")
    endif()
endif()

# Warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(WARNING_FLAGS "/Wall /wd4061 /wd4355 /wd4371 /wd4514 /wd4625 /wd4626 /wd4710 /wd4711 /wd4820 /wd5026 /wd5027 /wd5045 /wd26495 /WX")
else()
    set(WARNING_FLAGS "-Wall -Wextra")
    if (NOT DEFINED NO_WERROR)
        set(WARNING_FLAGS "${WARNING_FLAGS} -Werror")
    endif()
endif()

# Set compiler flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG_INIT} ${WARNING_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} ${WARNING_FLAGS}")
    set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE_INIT} ${WARNING_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} ${WARNING_FLAGS}")
else()
    set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG_INIT} ${WARNING_FLAGS} -Og -g3 -ggdb3 -fno-inline")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} ${WARNING_FLAGS} -Og -g3 -ggdb3 -fno-inline")
    set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE_INIT} ${WARNING_FLAGS} -O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} ${WARNING_FLAGS} -O2 -DNDEBUG")
endif()

# Enable unit tests
if(NOT DEFINED DISABLE_UNIT_TESTS)
    enable_testing()
endif()

# Default output directories
if(NOT DEFINED BIN_DIR)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${TARGET})
endif()
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# SDL library
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

# Assets directory
add_definitions(-DASSETS_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/assets")

# Sources
add_subdirectory(src)

# Examples
add_subdirectory(examples)
