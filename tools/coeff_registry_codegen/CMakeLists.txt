add_executable(coeff_registry_codegen
    main.cc
    schmidt.cc
    scalegh.cc
)

target_include_directories(coeff_registry_codegen
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_features(coeff_registry_codegen PRIVATE cxx_std_17)

if(BUILD_TESTING)
    add_executable(coeff_registry_codegen_schmidt_test
        schmidt_test.cc
        schmidt.cc
    )

    target_include_directories(coeff_registry_codegen_schmidt_test
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    target_compile_features(coeff_registry_codegen_schmidt_test PRIVATE cxx_std_17)

    add_test(NAME coeff_registry_codegen_schmidt_test COMMAND coeff_registry_codegen_schmidt_test)
endif()
