# Defines the base filename of the library
set( ATL_CORE_COMMOM_LIB_NAME_BASE atl_core_common )

# Defines the final library name (versioned or not)
set( ATL_CORE_COMMON_VERSION "${1.0.0}" )

# Output library name is the same than input in current releases
set( ATL_CORE_COMMON_LIB_NAME_OUTPUT ${ATL_CORE_COMMOM_LIB_NAME_BASE} )

add_library( ${ATL_CORE_COMMON_LIB_NAME_OUTPUT} STATIC
    Timer.cpp
    MtCmdQueue.cpp
    FileWatcher.cpp
)
   
add_library( ATLCore::${ATL_CORE_COMMOM_LIB_NAME_BASE} ALIAS ${ATL_CORE_COMMON_LIB_NAME_OUTPUT} )

target_link_libraries( ${ATL_CORE_COMMON_LIB_NAME_OUTPUT}
    Boost::filesystem
    Boost::program_options
    # date::date
)

target_include_directories( ${ATL_CORE_COMMON_LIB_NAME_OUTPUT}
    PUBLIC
    # ${libsigc++_INCLUDE_DIRS}
    $<INSTALL_INTERFACE:include/common>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Common>
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Templates>
)

target_compile_features(${ATL_CORE_COMMON_LIB_NAME_OUTPUT} PUBLIC cxx_std_17)

if( ATL_RELEASE_VERSION )
   target_compile_definitions( ${ATL_CORE_COMMON_LIB_NAME_OUTPUT} PUBLIC -DATL_RELEASE_VERSION )
endif()

# To install
include( GNUInstallDirs )
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ATLCoreCommon )

install( TARGETS ${ATL_CORE_COMMON_LIB_NAME_OUTPUT}
    EXPORT atl_core_common-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install( FILES
    Timer.hpp
    BitUtils.hpp
    MtQueue.hpp
    MtCmdQueue.hpp
    FlagModifier.hpp
    FileWatcher.hpp
    SimpleObjectPool.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/common
)

message( STATUS " atl_core_common-targets is ${atl_core_common-targets}" )

install(EXPORT atl_core_common-targets
    FILE
        ATLCoreCommon.cmake
    NAMESPACE
        ATLCore::
    DESTINATION
        ${INSTALL_CONFIGDIR}
    )

include( CMakePackageConfigHelpers )

# Helps making the resulting package relocatable by avoiding hardcoded paths
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/ATLCoreCommonConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommonConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommonConfigVersion.cmake
    VERSION ${ATL_CORE_COMMON_VERSION}
    COMPATIBILITY AnyNewerVersion
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommonConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreCommonConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
    )

export(EXPORT atl_core_common-targets
    FILE ${CMAKE_BINARY_DIR}/ATLCoreCommonTargets.cmake
    NAMESPACE ATLCore::
    )

message( STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}" )
message( STATUS " INSTALL_CONFIGDIR ${INSTALL_CONFIGDIR}" )
