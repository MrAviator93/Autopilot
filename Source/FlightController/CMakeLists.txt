set( EXECUTABLE_NAME FlightController.out )

add_executable( ${EXECUTABLE_NAME}
    launcher.cpp
)

target_include_directories( ${EXECUTABLE_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Core>
)

target_link_libraries( ${EXECUTABLE_NAME}
    ATL::Core
    boost_filesystem
    fmt
    pthread
)