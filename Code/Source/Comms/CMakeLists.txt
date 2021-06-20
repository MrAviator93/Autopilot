# Defines the base filename of the library
set( ATL_CORE_COMMS_LIB_NAME_BASE atl_core_comms )

# Defines the final library name (versioned or not)
set( ATL_CORE_COMMS_VERSION "${1.0.0}" )

# Output library name is the same than input in current releases
set( ATL_CORE_COMMS_LIB_NAME_OUTPUT ${ATL_CORE_COMMS_LIB_NAME_BASE} )

add_library( ${ATL_CORE_COMMS_LIB_NAME_OUTPUT} STATIC
    UDPClientThread.cpp
)
   
add_library(ATLCore::${ATL_CORE_COMMS_LIB_NAME_BASE} ALIAS ${ATL_CORE_COMMS_LIB_NAME_OUTPUT} )

target_link_libraries( ${ATL_CORE_COMMS_LIB_NAME_OUTPUT}
    Boost::filesystem
    Boost::program_options
    # date::date
)
target_include_directories( ${ATL_CORE_COMMS_LIB_NAME_OUTPUT}
    PUBLIC
    # ${libsigc++_INCLUDE_DIRS}
    $<INSTALL_INTERFACE:include/comms>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Comms>
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Common>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Templates>
)

target_compile_features(${ATL_CORE_COMMS_LIB_NAME_OUTPUT} PUBLIC cxx_std_17)

if(ATL_RELEASE_VERSION)
   target_compile_definitions( ${ATL_CORE_COMMS_LIB_NAME_OUTPUT} PUBLIC -DATL_RELEASE_VERSION )
endif()

# To install
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ATLCoreComms)

install(TARGETS ${ATL_CORE_COMMS_LIB_NAME_OUTPUT}
    EXPORT atl_core_comms-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(FILES
    UDPClientThread.hpp
    UDPMessage.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/comms
)

message( STATUS " atl_core_comms-targets is ${atl_core_comms-targets}")

install(EXPORT atl_core_comms-targets
    FILE
        ATLCoreComms.cmake
    NAMESPACE
        ATLCore::
    DESTINATION
        ${INSTALL_CONFIGDIR}
    )

include(CMakePackageConfigHelpers)

# Helps making the resulting package relocatable by avoiding hardcoded paths
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/ATLCoreCommsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommsConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommsConfigVersion.cmake
    VERSION ${ATL_CORE_COMMS_VERSION}
    COMPATIBILITY AnyNewerVersion
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommsConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
    )

export(EXPORT atl_core_comms-targets
    FILE ${CMAKE_BINARY_DIR}/ATLCoreCommsTargets.cmake
    NAMESPACE ATLCore::
    )


message( STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}" )
message( STATUS " INSTALL_CONFIGDIR ${INSTALL_CONFIGDIR}" )