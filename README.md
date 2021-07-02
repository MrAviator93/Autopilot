# Autopilot
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




