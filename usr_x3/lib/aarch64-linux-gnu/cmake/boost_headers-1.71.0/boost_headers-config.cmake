# Generated by Boost 1.71.0

if(TARGET Boost::headers)
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "Found boost_headers ${boost_headers_VERSION} at ${boost_headers_DIR}")
endif()

# Compute the include and library directories relative to this file.
get_filename_component(_BOOST_CMAKEDIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
get_filename_component(_BOOST_INCLUDEDIR "${_BOOST_CMAKEDIR}/../../../include/" ABSOLUTE)
get_filename_component(_BOOST_LIBDIR "${_BOOST_CMAKEDIR}/../" ABSOLUTE)

# Create imported target Boost::headers
add_library(Boost::headers INTERFACE IMPORTED)

set_target_properties(Boost::headers PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
  INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB"
)

unset(_BOOST_LIBDIR)
unset(_BOOST_INCLUDEDIR)
unset(_BOOST_CMAKEDIR)

mark_as_advanced(boost_headers_DIR)
