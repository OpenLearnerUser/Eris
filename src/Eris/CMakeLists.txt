set(target Eris)

set(root_dir  ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(header_dir ${root_dir}/include/${target}) 

file(GLOB headers ${header_dir}/*.h ${header_dir}/details/*.h)

file(GLOB source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(Eris_head_gen_py ${CMAKE_SOURCE_DIR}/scripts/header_gen.py)

if(NOT DEFINED PYTHON_EXECUTABLE)
    find_program(
        PYTHON_EXECUTABLE NAMES
        pyhton py python3
        REQUIRED
    )
endif()

add_custom_command(
  COMMAND ${PYTHON_EXECUTABLE} ${Eris_head_gen_py}
  DEPENDS ${headers}

  OUTPUT ${root_dir}/include/Eris.h

)
add_custom_target(
    Eris_head_gen_py  ALL DEPENDS ${root_dir}/include/Eris.h
)

add_library(${target}  ${source}  )

add_dependencies(${target} Eris_head_gen_py)

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}

    PUBLIC

    INTERFACE
)

target_link_libraries(${target}
   PRIVATE

   PUBLIC 
    ${DEFAULT_LINKER_OPTIONS}
    ${DEFAULT_LIBRARIES}

    INTERFACE

)

# Includes
target_include_directories(${target}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    #${CMAKE_CURRENT_SOURCE_DIR}/3rdparty

    PUBLIC

    INTERFACE
    $<BUILD_INTERFACE:${header_dir}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS ${target} DESTINATION ${root_dir}/install/lib EXPORT ${target}_Export)
install(DIRECTORY ${header_dir} DESTINATION ${root_dir}/install/include)
install(EXPORT  ${target}_Export
        DESTINATION ${root_dir}/install/lib/${target}
        FILE ${target}Config.cmake
)
