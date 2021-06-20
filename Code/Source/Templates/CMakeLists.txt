# Defines the base filename of the library
set( ATL_CORE_TEMPLATES_LIB_NAME_BASE atl_core_templates )

# Defines the final library name (versioned or not)
set( ATL_CORE_TEMPLATES_VERSION "${1.0.0}" )

# Output library name is the same than input in current releases
set( ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT ${ATL_CORE_TEMPLATES_LIB_NAME_BASE} )

add_library( ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT} STATIC 
   empty.cpp
)
   
add_library(ATLCore::${ATL_CORE_TEMPLATES_LIB_NAME_BASE} ALIAS ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT} )

target_link_libraries( ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT}
    Boost::filesystem
    Boost::program_options
    # date::date
)

target_include_directories( ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT}
    PUBLIC
    # ${libsigc++_INCLUDE_DIRS}
    $<INSTALL_INTERFACE:include/templates>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Templates>
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source/Common>
)

target_compile_features(${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT} PUBLIC cxx_std_17)
if(ATL_RELEASE_VERSION)
   target_compile_definitions( ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT} PUBLIC -DATL_RELEASE_VERSION )
endif()

# To install
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ATLCoreTemplates)

install(TARGETS ${ATL_CORE_TEMPLATES_LIB_NAME_OUTPUT}
    EXPORT atl_core_templates-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(FILES
    Counter.hpp
    NonCopyableMovable.hpp
    Singleton.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/templates
)

message( STATUS " atl_core_templates-targets is ${atl_core_templates-targets}")

install(EXPORT atl_core_templates-targets
    FILE
        ATLCoreTemplates.cmake
    NAMESPACE
        ATLCore::
    DESTINATION
        ${INSTALL_CONFIGDIR}
    )

include(CMakePackageConfigHelpers)

# Helps making the resulting package relocatable by avoiding hardcoded paths
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/ATLCoreTemplatesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreTemplatesConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreTemplatesConfigVersion.cmake
    VERSION ${ATL_CORE_TEMPLATES_VERSION}
    COMPATIBILITY AnyNewerVersion
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreTemplatesConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ATLCoreTemplatesConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
    )

# export(EXPORT atl_core_templates-targets
#     FILE ${CMAKE_BINARY_DIR}/ATLCoreTemplatesTargets.cmake
#     NAMESPACE ATLCore::
#     )


message( STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}" )
message( STATUS " INSTALL_CONFIGDIR ${INSTALL_CONFIGDIR}" )