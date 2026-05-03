#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Boost::atomic" for configuration ""
set_property(TARGET Boost::atomic APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Boost::atomic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/boost/lib/libboost_atomic.a"
  )

list(APPEND _cmake_import_check_targets Boost::atomic )
list(APPEND _cmake_import_check_files_for_Boost::atomic "${_IMPORT_PREFIX}/boost/lib/libboost_atomic.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
