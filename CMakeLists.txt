cmake_minimum_required(VERSION 3.4...3.28)
project(MyProject VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_TESTING "Build test executables" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Fallback for CMake versions < 3.21
if(NOT DEFINED PROJECT_IS_TOP_LEVEL)
  if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(PROJECT_IS_TOP_LEVEL TRUE)
  else()
    set(PROJECT_IS_TOP_LEVEL FALSE)
  endif()
endif()

if(NOT PROJECT_IS_TOP_LEVEL)
  set(BUILD_TESTING OFF)
  option(${PROJECT_NAME}_BUILD_TESTING "Build ${PROJECT_NAME} test executables" OFF)
  option(${PROJECT_NAME}_INSTALL "Install ${PROJECT_NAME} targets" OFF)
endif()

# Project-wide setup
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)

# Dependencies
# TODO: Add find_package() calls here

# Targets
if(BUILD_TESTING)
  enable_testing()

  # TODO: If you have a test driver, call find_package(... REQUIRED) here
endif()

add_subdirectory(lib1)
add_subdirectory(lib2)

# Testing
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Installation
if(PROJECT_IS_TOP_LEVEL OR ${PROJECT_NAME}_INSTALL)
  if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install" CACHE PATH "" FORCE)
  endif()

  include(GNUInstallDirs)
  install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )
  include(CMakePackageConfigHelpers)
  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )
  write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )
  install(FILES
      ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
      ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )
endif()
