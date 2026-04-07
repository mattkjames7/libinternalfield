cmake_minimum_required(VERSION 3.20)

set(LIBINTERNALFIELD_TEST_WORKDIR "${CMAKE_CURRENT_SOURCE_DIR}")

include(FetchContent)
find_package(GTest CONFIG QUIET)
if (NOT GTest_FOUND)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

add_library(libinternalfield_testdata OBJECT
    testdata.cc
    testdata.h)

target_include_directories(libinternalfield_testdata PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(libinternalfield_gtest
    gtest_unit.cc
    $<TARGET_OBJECTS:libinternalfield_testdata>)
target_include_directories(libinternalfield_gtest
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)
target_link_libraries(libinternalfield_gtest
    PRIVATE
        internalfield
        GTest::gtest_main)

gtest_discover_tests(libinternalfield_gtest
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(libinternalfield_cpptest cpptest.cc)
target_include_directories(libinternalfield_cpptest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_cpptest PRIVATE internalfield)
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_cpptest PRIVATE m)
endif()

add_executable(libinternalfield_ctest ctest.c)
target_include_directories(libinternalfield_ctest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_ctest PRIVATE internalfield)
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_ctest PRIVATE m)
endif()

add_executable(libinternalfield_timer timer.cc)
target_include_directories(libinternalfield_timer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_timer PRIVATE internalfield)
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_timer PRIVATE m)
endif()

add_executable(libinternalfield_savetestdata
    save_test_data/savetestdata.cc
    testdata.cc
)
target_include_directories(libinternalfield_savetestdata
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/save_test_data"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)
target_link_libraries(libinternalfield_savetestdata PRIVATE internalfield)
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_savetestdata PRIVATE m)
endif()

add_test(NAME internalfield_c_api COMMAND libinternalfield_ctest)
set_tests_properties(internalfield_c_api PROPERTIES
    WORKING_DIRECTORY "${LIBINTERNALFIELD_TEST_WORKDIR}"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

add_test(NAME internalfield_cpp_api COMMAND libinternalfield_cpptest)
set_tests_properties(internalfield_cpp_api PROPERTIES
    WORKING_DIRECTORY "${LIBINTERNALFIELD_TEST_WORKDIR}"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

add_test(NAME internalfield_timer COMMAND libinternalfield_timer)
set_tests_properties(internalfield_timer PROPERTIES
    WORKING_DIRECTORY "${LIBINTERNALFIELD_TEST_WORKDIR}"
)
