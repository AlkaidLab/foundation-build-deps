#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Boost::log_setup" for configuration ""
set_property(TARGET Boost::log_setup APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Boost::log_setup PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/boost/lib/libboost_log_setup-clang22-mt-a64-1_89.a"
  )

list(APPEND _cmake_import_check_targets Boost::log_setup )
list(APPEND _cmake_import_check_files_for_Boost::log_setup "${_IMPORT_PREFIX}/boost/lib/libboost_log_setup-clang22-mt-a64-1_89.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
