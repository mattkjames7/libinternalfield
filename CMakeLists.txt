cmake_minimum_required(VERSION 3.20)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" LIBINTERNALFIELD_VERSION_RAW)
string(STRIP "${LIBINTERNALFIELD_VERSION_RAW}" LIBINTERNALFIELD_VERSION)

project(libinternalfield VERSION ${LIBINTERNALFIELD_VERSION} LANGUAGES C CXX)

include(CTest)
option(LIBINTERNALFIELD_BUILD_TESTS "Build test executables" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LIBINTERNALFIELD_BUILD_SHARED "Build shared library" ON)
option(LIBINTERNALFIELD_BUILD_STATIC "Build static library" ON)

if(NOT LIBINTERNALFIELD_BUILD_SHARED AND NOT LIBINTERNALFIELD_BUILD_STATIC)
    message(FATAL_ERROR "At least one of LIBINTERNALFIELD_BUILD_SHARED or LIBINTERNALFIELD_BUILD_STATIC must be ON")
endif()

add_subdirectory(tools/coeff_registry_codegen)

set(GENERATED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/generated/out.h")

file(GLOB_RECURSE LIBINTERNALFIELD_COEFF_INPUTS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/data/coeffs/*/*.dat"
)

add_custom_command(
    OUTPUT "${GENERATED_HEADER}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/generated"
    COMMAND coeff_registry_codegen "${CMAKE_CURRENT_SOURCE_DIR}/data/coeffs" "${GENERATED_HEADER}"
    DEPENDS
        coeff_registry_codegen
        "${CMAKE_CURRENT_SOURCE_DIR}/data/igrf/igrf13coeffs.txt"
        ${LIBINTERNALFIELD_COEFF_INPUTS}
    COMMENT "Generating model registry header"
    VERBATIM
)

add_custom_target(generate_model_registry DEPENDS "${GENERATED_HEADER}")

set(LIBINTERNALFIELD_SOURCES
    src/models.cc
    src/internal.cc
    src/internalmodel.cc
    src/libinternal.cc
)

add_library(libinternalfield_obj OBJECT ${LIBINTERNALFIELD_SOURCES})
add_dependencies(libinternalfield_obj generate_model_registry)
set_target_properties(libinternalfield_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(libinternalfield_obj
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_obj PRIVATE m)
endif()

if(LIBINTERNALFIELD_BUILD_SHARED)
    add_library(internalfield SHARED $<TARGET_OBJECTS:libinternalfield_obj>)
    set_target_properties(internalfield PROPERTIES OUTPUT_NAME internalfield)
    target_include_directories(internalfield
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    if(UNIX AND NOT APPLE)
        target_link_libraries(internalfield PRIVATE m)
    endif()
endif()

if(LIBINTERNALFIELD_BUILD_STATIC)
    add_library(internalfield_static STATIC $<TARGET_OBJECTS:libinternalfield_obj>)
    set_target_properties(internalfield_static PROPERTIES OUTPUT_NAME internalfield)
    target_include_directories(internalfield_static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    if(UNIX AND NOT APPLE)
        target_link_libraries(internalfield_static PRIVATE m)
    endif()
endif()

if(LIBINTERNALFIELD_BUILD_TESTS AND BUILD_TESTING)
    add_subdirectory(test)
endif()

include(GNUInstallDirs)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/internalfield.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(TARGET internalfield)
    install(TARGETS internalfield
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

if(TARGET internalfield_static)
    install(TARGETS internalfield_static
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()
