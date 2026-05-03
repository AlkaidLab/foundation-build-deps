#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Boost::wserialization" for configuration ""
set_property(TARGET Boost::wserialization APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Boost::wserialization PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/boost/lib/libboost_wserialization-clang22-mt-a64-1_89.a"
  )

list(APPEND _cmake_import_check_targets Boost::wserialization )
list(APPEND _cmake_import_check_files_for_Boost::wserialization "${_IMPORT_PREFIX}/boost/lib/libboost_wserialization-clang22-mt-a64-1_89.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
