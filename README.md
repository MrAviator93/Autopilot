# Autopilot

# Table of contents
* [Description](#Description)
* [Motivation](#Motivation)
* [Requirements](#Requirements)
* [3rd Party](#3rd-Party)
* [Dev Environment and Format](#Dev-Environment-and-Formatting)
* [Cross-compilation](#Cross-compilation)
* [Build-Linux](#Build-Linux)
* [Build-Windows](#Build-Windows)
* [VCPKG-Notes](#VCPKG-Notes)

# Description
WIP. Autopilot is a PET type project that actually consists of three sub-projects: 
1. Core library, based on which everything is build.
2. Onboard flight control system for an UAV (to be deployed on Raspberry Pi 4)
3. Ground station (to be deployed on either Windows or Linux platform)

The 2 sub-projects: the Onboard flight control system and Ground station
will be moved to separate projects - separate repositories soon.

# Motivation
Appart from being a C++ software engineer I am also an Aerospace Systems Engineer. Therefore, I also have a certain interest in the UAV technology. 

# Requirements
A C++ compiler that supports C++ 17 revision, Boost C++ libraries and fmt formatting library.

# 3rd-Party
The CMake project is made to be buildable on Linux platform inconjunction with it's default package manager
as well as Windows platform with vcpkg package manager.

It is strongly recomended where possible to use package managers to install 3rd Party Libraries

## Boost
For latest version of boost libraries see:<br/>
https://www.boost.org/

If using package managers to install Boost libraries use one of the following commands:<br/>
```
sudo apt-get install libboost*.**-dev
```

```
 .\vcpkg.exe install boost:x64-windows-static
```

## FMT
For fmtlib you have the choise either to clone the following repository:<br/>
https://github.com/fmtlib/fmt<br/>
Or to use package managers to install the library.<br/>

```
sudo apt-get install libfmt-dev
```
```
 .\vcpkg.exe install fmt:x64-windows-static
```
## Pugi-XML
For settings we use boost_options library and pugixml
Therefore install:
```
sudo apt-get install libpugixml-dev
```

```
 .\vcpkg.exe install pugixml:x64-windows-static
```
## Hinant Date
For date library, clone the following repository:<br/>
https://github.com/HowardHinnant/date

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
vcpkg install date
```

## X11
For X11 windowing system install the x11 library (applicable only to Linux based systems):<br/>
```
sudo apt-get install libx11-dev
```

It's also necessery to install mesa-utils:<br/>
```
sudo apt-get install mesa-utils
```

It may be also necessery to install the following libs for windowing to work:<br/>
```
mesa-common-dev mesa-utils-extra libgl1-mesa-dev libglu1-mesa-dev libglapi-mesa libxi-dev libxinerama-dev libxcursor-dev libxrandr-dev
```

## GLM
GLM is used for graphics related mathematical operations:<br/>
```
sudo apt-get install libglm-dev
```

```
.\vcpkg.exe install glm:x64-windows-static
```

## Doctest
All unit tests are made with the use of Doctest:<br/>
```
sudo apt-get install -y doctest
```

```
.\vcpkg.exe install pugixml:x64-windows-static
```

## LIBSIGC++
Used for signals - we use version 3.0

```
https://www.linuxfromscratch.org/blfs/view/svn/general/libsigc3.html

Extract
cd build
cmake ../
sudo make install

```

```
.\vcpkg.exe install libsigcpp-3:x64-windows-static
```

For Windows - vcpkg configuration it will be also necessery to edit __sigc++config.h__ file:

1. ```vcpkg\installed\x64-windows-static\lib\sigc++-3.0\include\sigc++config.h```

And actually it is necessery to one of them the "sigc++config.h"
```
/* Detect Win32 platform */
#ifdef _WIN32
# if defined(_MSC_VER)
#  define SIGC_MSC 1
#  define SIGC_WIN32 1
#  define SIGC_DLL 1
# elif defined(__CYGWIN__)
#  define SIGC_CONFIGURE 1
# elif defined(__MINGW32__)
#  define SIGC_WIN32 1
#  define SIGC_CONFIGURE 1
# else
#  error "libsigc++ config: Unknown win32 architecture (send me gcc --dumpspecs or equiv)"
# endif
#else /* !_WIN32 */
# define SIGC_CONFIGURE 1
#endif /* !_WIN32 */
```

For static builds we don't want __#  define SIGC_DLL 1__ to be defined!

# Dev-Environment-and-Formatting
The project development is carried out in Visual Studio Code, in order to be able to autoformat the Clang-Format application must be installed on the operating system.
Additionally the project comes with the .clang-format file, which contains the formating instructions for Clang-Format application.

1. Check that inside _"/Code/"_ directory there is _.clan-format_ file
2. Install Clang Format app ( in linux ```sudo apt-get install clang-format``` )
3. In VS Code install the following extension: Clang-Format 1.10.0 by Michael Johns

# Cross-compilation
To install Docker follow the following document:<br/>
https://docs.docker.com/engine/install/ubuntu/

# Build-Linux
To build and install the libraries do the following:
* In root folder run configure.py script
* cd into the Build folder
* make -j8 (or num of available threads)
* sudo make install

# Build-Windows
To build and install the libraries do the following:
* In root folder run configure.py script
* Navigate to the Build folder and you will find*.sln file
* Open the solution file with the visual studio code or double click it to start
* Choose the deployment type (Debug or Release)
* Build Solution (F7)
* Switch to INSTALL
* Build Solution (F7)
You libraries will be installed under: "C:\usr\local\ directory"

# Windows Notes
To compile the VADCore for windows see the following link:<br/>
__https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md#cmake-toolchain-file__

The best way to use installed libraries with cmake is via the toolchain file scripts\buildsystems\vcpkg.cmake.
To use this file, you simply need to add it onto your CMake command line as:
```
-DCMAKE_TOOLCHAIN_FILE=D:\src\vcpkg\scripts\buildsystems\vcpkg.cmake.
```

## Building using MSBuild 
The following information will allow you to build the project using MSBuild.exe or build-release.py and build-debug.py scripts,
without starting Visual Studio.

To enable msbuild in Command Prompt, you simply must add the directory of the msbuild.exe to the PATH environment variable.

You can access the environment variables by:
1. Right clicking on Computer
2. Click Properties
3. Then click Advanced system settings on the left navigation bar
4. On the next dialog box click Environment variables
5. Scroll down to PATH
6. Edit it to include your path to the framework (don't forget a ";" after the last entry in here).
7. For reference, my path was C:\Windows\Microsoft.NET\Framework\v4.0.30319

Path Updates:
* As of MSBuild 12 (2013)/VS 2013/.NET 4.5.1+ and onward MSBuild is now installed as a part of Visual Studio.
* For VS2015 the path was %ProgramFiles(x86)%\MSBuild\14.0\Bin
* For VS2017 the path was %ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin
* For VS2019 the path was %ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin

