set( LIB_NAME ATLCore)

add_library( ${LIB_NAME} STATIC
    ISATable.cpp  
    CTimer.cpp
)

add_library( ATL::Core ALIAS ${LIB_NAME} )

add_subdirectory( Math )

target_include_directories( ${LIB_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Core/Math>
    PRIVATE
)

target_link_libraries( ${LIB_NAME} 
    ATL::Math
    boost_filesystem
    boost_program_options
    fmt
    pthread
)