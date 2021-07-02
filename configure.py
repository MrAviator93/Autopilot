#! /usr/bin/python3

import os
import platform

print( "Configuring the project .... " )

configure_flags = ""

pl_name = platform.system()
print( pl_name )

if pl_name == "Linux":
    print( platform.linux_distribution()[ 0 ] )    

# TODO: This script must take into account to which platform we are building!
    
if os.path.exists( "Build/" ) != True:
    os.mkdir( "Build" )
    os.chdir( "Build" )
    os.system( "cmake ../Code {}".format( configure_flags ) )
else:
    print( "Build directory already exists, delete it to reconfigure..." )

