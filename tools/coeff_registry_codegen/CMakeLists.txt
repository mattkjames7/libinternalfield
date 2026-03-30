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
