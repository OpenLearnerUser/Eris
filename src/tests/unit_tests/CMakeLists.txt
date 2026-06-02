set(target unit_tests)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EXTERNAL_DIR}/googletest/googlemock/include
    ${EXTERNAL_DIR}/googletest/googletest/include
    )
file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )


add_executable(${target} ${sources})

set_target_properties(
    ${target} PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

# Compile options
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        /wd4189       # -> disable warning: 'xxx': local variable is initialized but not referenced
        /wd4244       # -> disable warning: 'initializing': conversion from 'unsigned __int64' to 'unsigned int', possible loss of data
        /wd4267       # -> disable warning: '=': conversion from 'size_t' to 'int', possible loss of data
        /wd4996       # -> disable warning: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
        )
endif ()

# GCC and Clang compiler options
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        -Wno-sign-compare
        -Wno-unused-parameter
        -Wno-strict-aliasing
        )
endif ()

target_compile_options(
    ${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)

# Link libraries
target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    Eris
    gmock
    gtest
    gtest_main)


