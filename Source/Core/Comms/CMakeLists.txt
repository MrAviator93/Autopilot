set( LIB_NAME ATLComms)

add_library( ${LIB_NAME} STATIC
    General.cpp
)

add_library( ATL::Comms ALIAS ${LIB_NAME} )

target_include_directories( ${LIB_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Core/Comms>
    PRIVATE
)

target_link_libraries( ${LIB_NAME} 
    boost_filesystem
    boost_program_options
    fmt
    pthread
)