#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "charls" for configuration "None"
set_property(TARGET charls APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(charls PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libcharls.so.2.3.4"
  IMPORTED_SONAME_NONE "libcharls.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS charls )
list(APPEND _IMPORT_CHECK_FILES_FOR_charls "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libcharls.so.2.3.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
