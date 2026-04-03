cmake_minimum_required(VERSION 3.20)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" LIBINTERNALFIELD_VERSION_RAW)
string(STRIP "${LIBINTERNALFIELD_VERSION_RAW}" LIBINTERNALFIELD_VERSION)

project(libinternalfield VERSION ${LIBINTERNALFIELD_VERSION} LANGUAGES C CXX)

include(CTest)
option(LIBINTERNALFIELD_BUILD_TESTS "Build test executables" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

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

add_library(internalfield ${LIBINTERNALFIELD_SOURCES})
add_dependencies(internalfield generate_model_registry)

target_include_directories(internalfield
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(UNIX AND NOT APPLE)
    target_link_libraries(internalfield PRIVATE m)
endif()

if(LIBINTERNALFIELD_BUILD_TESTS AND BUILD_TESTING)
    add_subdirectory(test)
endif()

include(GNUInstallDirs)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/internalfield.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS internalfield
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
