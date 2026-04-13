# CMake version
cmake_minimum_required(VERSION 3.12.8 FATAL_ERROR)
# Declare project
project(Eris)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)
include_directories(external)


message("CMake build Type:" ${CMAKE_BUILD_TYPE})
if (NOT ${CMAKE_BUILD_TYPE})
    SET(CMAKE_BUILD_TYPE Debug)
    add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Release") 
    set(CMAKE_BUILD_TYPE Release)
endif()

# Configure tasking system backend
include(cmake/TaskingSystemOptions.cmake)

# Compile options
include(cmake/CompileOptions.cmake)

set(CMAKE_MACOSX_RPATH ON)


# Target name
set(target hello_fluid_sim)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Sources
file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build executable
add_executable(${target}
    ${sources})









