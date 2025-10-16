#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "draco_static" for configuration "None"
set_property(TARGET draco_static APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(draco_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NONE "CXX"
  IMPORTED_LOCATION_NONE "/usr/lib/aarch64-linux-gnu/libdraco.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS draco_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_draco_static "/usr/lib/aarch64-linux-gnu/libdraco.a" )

# Import target "draco_shared" for configuration "None"
set_property(TARGET draco_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(draco_shared PROPERTIES
  IMPORTED_LOCATION_NONE "/usr/lib/aarch64-linux-gnu/libdraco.so.4.0.0"
  IMPORTED_SONAME_NONE "libdraco.so.4"
  )

list(APPEND _IMPORT_CHECK_TARGETS draco_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_draco_shared "/usr/lib/aarch64-linux-gnu/libdraco.so.4.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
