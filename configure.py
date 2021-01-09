#!/usr/bin/env python
# To make an executable use the following: chmod +x <filename>.py

import os
import os.path
from os import path

import string

# Global variable definitions
PROJECT_NAME = "Autopilot"

BUILD_DIR = "Build/Make/"
CMAKE_VERSION_REQ = "3.10"
CXX_STANDARD_VERSION = "17"

# Write CMakeLists file function
def writeCMakeLists( ):
    outFile = open( "CMakeLists.txt", "w" )
    outFile.write( "cmake_minimum_required(VERSION {})\n\n".format( CMAKE_VERSION_REQ ) )
    outFile.write( "project( {} )\n\n".format( PROJECT_NAME ) )
    outFile.write( "set( CMAKE_CXX_STANDARD {} )\n".format( CXX_STANDARD_VERSION ) )
    outFile.write( "set( CMAKE_CXX_STANDARD_REQUIRED TRUE )\n\n" )
    outFile.write( "add_subdirectory( Source )\n" )
    outFile.close()

# Beginning of the main script
if ( os.path.exists( BUILD_DIR ) == False ):
    os.makedirs( BUILD_DIR )

writeCMakeLists()

        


