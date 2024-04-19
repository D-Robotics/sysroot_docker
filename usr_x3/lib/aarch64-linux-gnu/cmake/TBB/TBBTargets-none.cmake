#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TBB::tbb" for configuration "None"
set_property(TARGET TBB::tbb APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(TBB::tbb PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbb.so.12.5"
  IMPORTED_SONAME_NONE "libtbb.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS TBB::tbb )
list(APPEND _IMPORT_CHECK_FILES_FOR_TBB::tbb "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbb.so.12.5" )

# Import target "TBB::tbbmalloc" for configuration "None"
set_property(TARGET TBB::tbbmalloc APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(TBB::tbbmalloc PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbbmalloc.so.2.5"
  IMPORTED_SONAME_NONE "libtbbmalloc.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS TBB::tbbmalloc )
list(APPEND _IMPORT_CHECK_FILES_FOR_TBB::tbbmalloc "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbbmalloc.so.2.5" )

# Import target "TBB::tbbmalloc_proxy" for configuration "None"
set_property(TARGET TBB::tbbmalloc_proxy APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(TBB::tbbmalloc_proxy PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NONE "TBB::tbbmalloc"
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbbmalloc_proxy.so.2.5"
  IMPORTED_SONAME_NONE "libtbbmalloc_proxy.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS TBB::tbbmalloc_proxy )
list(APPEND _IMPORT_CHECK_FILES_FOR_TBB::tbbmalloc_proxy "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libtbbmalloc_proxy.so.2.5" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
