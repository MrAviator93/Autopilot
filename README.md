# Autopilot
WIP. Autopilot is a PET type project that actually consists of two sub-projects: 
1. Core library, based on which everything is build.
2. Onboard flight control system for an UAV (to be deployed on Raspberry Pi 4)
3. Ground station (to be deployed on either Windows or Linux platform)

The 2 sub-projects: the Onboard flight control system and Ground station
will be moved to separate projects - separate repositories soon.

# Motivation
Appart from being a C++ software engineer I am also an Aerospace Systems Engineer. Therefore, I also have a certain interest in the UAV technology. 

# Development Environment and Code Formatting
The project development is carried out in Visual Studio Code, in order to be able to autoformat the Clang-Format application must be installed on the operating system.
Additionally the project comes with the .clang-format file, which contains the formating instructions for Clang-Format application.

1. Inside "/Code/" directory .clan-format file
2. Install Clang Format app ( in linux sudo apt-get install clang-format )
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
To be writen.

# Requirements
A C++ compiler that supports C++ 17 revision, Boost C++ libraries and fmt formatting library.


