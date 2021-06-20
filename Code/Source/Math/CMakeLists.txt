# Defines the base filename of the library
set( ATL_CORE_MATH_LIB_NAME_BASE atl_core_math )

# Defines the final library name (versioned or not)
set( ATL_CORE_MATH_VERSION "${1.0.0}" )

# Output library name is the same than input in current releases
set( ATL_CORE_MATH_LIB_NAME_OUTPUT ${ATL_CORE_MATH_LIB_NAME_BASE} )

add_library( ${ATL_CORE_MATH_LIB_NAME_OUTPUT} STATIC
    Colour.cpp
    LinearColour.cpp
    BoundSphere.cpp
    BoundBox2D.cpp
    BoundBox3D.cpp
    Math.cpp
)
   
add_library(ATLCore::${ATL_CORE_MATH_LIB_NAME_BASE} ALIAS ${ATL_CORE_MATH_LIB_NAME_OUTPUT} )

target_link_libraries( ${ATL_CORE_MATH_LIB_NAME_OUTPUT}
    Boost::filesystem
    Boost::program_options
    pugixml
)
target_include_directories( ${ATL_CORE_MATH_LIB_NAME_OUTPUT}
    PUBLIC
    # ${libsigc++_INCLUDE_DIRS}
    $<INSTALL_INTERFACE:include/math>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Math>
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Templates>
)

target_compile_features(${ATL_CORE_MATH_LIB_NAME_OUTPUT} PUBLIC cxx_std_17)

if(ATL_RELEASE_VERSION)
   target_compile_definitions( ${ATL_CORE_MATH_LIB_NAME_OUTPUT} PUBLIC -DATL_RELEASE_VERSION )
endif()

# To install
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ATLCoreMath)

install(TARGETS ${ATL_CORE_MATH_LIB_NAME_OUTPUT}
    EXPORT atl_core_math-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(FILES
    Colour.hpp
    LinearColour.hpp
    ColourCommon.hpp
    BoundSphere.hpp
    BoundBox2D.hpp
    BoundBox3D.hpp
    Controllers.hpp
    Math.hpp
    ISAData.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/math
)

message( STATUS " atl_core_math-targets is ${atl_core_math-targets}")

install(EXPORT atl_core_math-targets
    FILE
        ATLCoreMath.cmake
    NAMESPACE
        ATLCore::
    DESTINATION
        ${INSTALL_CONFIGDIR}
    )

include(CMakePackageConfigHelpers)

# Helps making the resulting package relocatable by avoiding hardcoded paths
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/ATLCoreMathConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreMathConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreMathConfigVersion.cmake
    VERSION ${ATL_CORE_MATH_VERSION}
    COMPATIBILITY AnyNewerVersion
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreMathConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreMathConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
    )

export(EXPORT atl_core_math-targets
    FILE ${CMAKE_BINARY_DIR}/ATLCoreMathTargets.cmake
    NAMESPACE ATLCore::
    )


message( STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}" )
message( STATUS " INSTALL_CONFIGDIR ${INSTALL_CONFIGDIR}" )