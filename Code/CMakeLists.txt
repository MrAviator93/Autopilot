cmake_minimum_required( VERSION "3.20.0" )

project( ATLCore VERSION 1.0 LANGUAGES CXX )

if ( WIN32 )
    add_compile_definitions( ATL_PLATFORM_WINDOWS )
    message( "Windows platform detected ..." )
endif()

if ( UNIX AND NOT APPLE )
    # Can be one of the following: Linux, BSD, Solaris, Minix
    add_compile_definitions( ATL_PLATFORM_LINUX )
    message( "Linux based platform detected ..." )
endif()

if ( APPLE )
    # Can be one of the following: MacOS X or iOS, watchOS, tvOS
    add_compile_definitions( ATL_PLATFORM_APPLE )
    message( "Apple platform detected, but not supported!" )
endif()

# if(CMAKE_TOOLCHAIN_FILE)
#     include(${CMAKE_TOOLCHAIN_FILE})
# endif(CMAKE_TOOLCHAIN_FILE)

if ( WIN32 )
    add_compile_definitions( _WIN32_WINNT=0x0A00 )
    set( VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "We are building for x64 platform static libraries." )
    # set(CMAKE_TOOLCHAIN_FILE "C:/VCPCKG/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path for vcpkg.cmake")
    include( "C:/VCPCKG/vcpkg/scripts/buildsystems/vcpkg.cmake" )
endif()

option( ATL_RELEASE_VERSION "Compile as release version." OFF )
option( ATL_INCLUDE_COMPILE_TESTS "Additionally compile the unit tests." ON )
option( ATL_CORE_GENERATE_DOC "Generate documentation." OFF )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED TRUE )

if( MSVC )
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

# We are installing ATLCore libs for future
# in secondary project use.
set( CMAKE_INSTALL_PREFIX "/usr/local/atl")

set( Boost_USE_RELEASAE_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_RUNTIME ON )

find_package( Boost REQUIRED COMPONENTS program_options system filesystem )

if ( UNIX AND NOT APPLE )
    include_directories( ${BOOST_INCLUDEDIR} )
endif()

if ( WIN32 )
    include_directories( ${Boost_INCLUDE_DIRS} )
endif()

find_package( pugixml REQUIRED )
find_package( fmt CONFIG REQUIRED )
find_package( date REQUIRED )

add_subdirectory( Source )

if ( ATL_INCLUDE_COMPILE_TESTS )
    message( "Building Test(s) ..." )
    add_subdirectory( Test )
endif()
