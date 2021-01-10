set( LIB_NAME ATLMath)

add_library( ${LIB_NAME} STATIC
    Math.cpp
    Dynamics.cpp
    GlobalPosition.cpp
)

add_library( ATL::Math ALIAS ${LIB_NAME} )

target_include_directories( ${LIB_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Core>
)

target_link_libraries( ${LIB_NAME}
    ATL::Core
)
