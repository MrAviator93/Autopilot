set( LIB_NAME ATLFController)

add_library( ${LIB_NAME} STATIC
    
)

add_library( ATL::FC::FController ALIAS ${LIB_NAME} )