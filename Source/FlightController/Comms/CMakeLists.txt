set( LIB_NAME ATLFCComms)

add_library( ${LIB_NAME} STATIC
    
)

add_library( ATL::FC::Comms ALIAS ${LIB_NAME} )