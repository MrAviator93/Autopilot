set( EXECUTABLE_OUT_NAME test_flag_modifier )

add_executable( ${EXECUTABLE_OUT_NAME} 
    MainFlagModifier.cpp
)

target_include_directories( ${EXECUTABLE_OUT_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Common>
)

target_compile_features( ${EXECUTABLE_OUT_NAME}
    PUBLIC
    cxx_std_17
)

target_link_libraries( ${EXECUTABLE_OUT_NAME}
    ATLCore::atl_core_common
    pthread
)
