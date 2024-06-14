# - Config file for the libuvc package

include(FindPackageHandleStandardArgs)
set(${CMAKE_FIND_PACKAGE_NAME}_CONFIG ${CMAKE_CURRENT_LIST_FILE})
find_package_handle_standard_args(libuvc CONFIG_MODE)

if(NOT TARGET libuvc::libuvc)
    include("${CMAKE_CURRENT_LIST_DIR}/libuvcTargets.cmake")
    if((NOT TARGET libuvc) AND
       (NOT libuvc_FIND_VERSION OR
        libuvc_FIND_VERSION VERSION_LESS 0.0.6))
        add_library(libuvc INTERFACE IMPORTED)
        set_target_properties(libuvc PROPERTIES
            INTERFACE_LINK_LIBRARIES libuvc::libuvc
        )
    endif()
endif()

