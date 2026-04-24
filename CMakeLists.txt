# CMake version
cmake_minimum_required(VERSION 3.12.8 FATAL_ERROR)
# Declare project
project(PEris)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)
include_directories(extern)


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

#进行代码覆盖率测试选项
option(BUILD_COVERAGE "Build code coverage" OFF)
if(CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage unit_tests coverage)
endif()

set(CMAKE_MACOSX_RPATH ON)

#TODO::资源文件处理



#项目模块
SET(BUILD_GTEST ON CACHE BOOL "" FORCE)
SET(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(extern/googletest EXCLUDE_FROM_ALL)

if ((CMAKE_VERSION VERSION_EQUAL 3.3) OR (CMAKE_VERSION VERSION_GREATER 3.3))
    cmake_policy(SET CMP0063 NEW)
endif()
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/benchmark)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)



add_subdirectory(src/Eris)









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

target_link_directories(${target}
PRIVATE
${DEFAULT_LINKER_OPTIONS}
Eris

)









