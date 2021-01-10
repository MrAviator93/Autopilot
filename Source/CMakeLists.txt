# Core is needed for all sub-projects
add_subdirectory(Core)

# Build flight controller only 
add_subdirectory(FlightController)

# ***** TODO: Add if else directives

# Build GroundStation only ( currently planned for Windows only )
#add_subdirectory(GroundStation)