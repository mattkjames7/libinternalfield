set(LIBINTERNALFIELD_TEST_WORKDIR "${CMAKE_CURRENT_SOURCE_DIR}")

if(TARGET internalfield)
    set(LIBINTERNALFIELD_TEST_LINK_TARGET internalfield)
elseif(TARGET internalfield_static)
    set(LIBINTERNALFIELD_TEST_LINK_TARGET internalfield_static)
else()
    message(FATAL_ERROR "No libinternalfield library target available for tests")
endif()

add_library(libinternalfield_testdata OBJECT testdata.cc)
target_include_directories(libinternalfield_testdata
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

target_link_libraries(libinternalfield_testdata PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})

if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_testdata PRIVATE m)
endif()

add_executable(libinternalfield_test test.cc $<TARGET_OBJECTS:libinternalfield_testdata>)
target_include_directories(libinternalfield_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_test PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_test PRIVATE m)
endif()

add_executable(libinternalfield_cpptest cpptest.cc)
target_include_directories(libinternalfield_cpptest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_cpptest PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_cpptest PRIVATE m)
endif()

add_executable(libinternalfield_ctest ctest.c)
target_include_directories(libinternalfield_ctest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_ctest PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_ctest PRIVATE m)
endif()

add_executable(libinternalfield_timer timer.cc)
target_include_directories(libinternalfield_timer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(libinternalfield_timer PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})
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
target_link_libraries(libinternalfield_savetestdata PRIVATE ${LIBINTERNALFIELD_TEST_LINK_TARGET})
if(UNIX AND NOT APPLE)
    target_link_libraries(libinternalfield_savetestdata PRIVATE m)
endif()

add_test(NAME internalfield_unit COMMAND libinternalfield_test)
set_tests_properties(internalfield_unit PROPERTIES
    WORKING_DIRECTORY "${LIBINTERNALFIELD_TEST_WORKDIR}"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

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
