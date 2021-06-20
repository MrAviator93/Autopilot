#! /usr/bin/python3

import os

build_path = "Build/Test/"
file_pattern = "test_"

print( "Running Unit Tests" )

if os.path.exists( build_path ):
    print( "Found {} directory...".format( build_path ) )
    print( "Preparing to execute test_* executables " )

    # Recursive lookup
    for r, d, f in os.walk( build_path ):
        for file in f:
            if file_pattern in file:
                cwd = os.getcwd()
                full_file_name = os.path.join( r, file )
                full_file_name = os.path.join( cwd, full_file_name )
                os.system( full_file_name )
else:
    print( "To run this script you must generate/build the project inside 'Build' folder!" )
