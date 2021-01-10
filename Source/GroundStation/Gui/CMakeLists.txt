set( LIB_NAME ATLGui)

add_library( ${LIB_NAME} STATIC

)

add_library( ATL::Comms ALIAS ${LIB_NAME} )

target_include_directories( ${LIB_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Core>
    PRIVATE
)

target_link_libraries( ${LIB_NAME} 
    ATL::Core
    boost_filesystem
    boost_program_options
    fmt
    pthread
)