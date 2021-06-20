#! /usr/bin/python3

import os

print( "Configuring the project .... " )

configure_flags = ""

if os.path.exists( "Build/" ) != True:
    os.mkdir( "Build" )
    os.chdir( "Build" )
    os.system( "cmake ../Code {}".format( configure_flags ) )
else:
    print( "Build directory already exists, delete it to reconfigure..." )

