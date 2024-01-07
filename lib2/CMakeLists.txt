add_library(${PROJECT_NAME}_Lib2 INTERFACE)
add_library(${PROJECT_NAME}::Lib2 ALIAS ${PROJECT_NAME}_Lib2)

set(PUBLIC_HEADERS

  # TODO: Add headers here
  include/MyProject/lib2/lib2.h
)

# Convert interface sources to absolute paths (required for CMake < 3.13)
foreach(SOURCE ${PUBLIC_HEADERS})
  list(APPEND ABSOLUTE_PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE})
endforeach()

target_sources(${PROJECT_NAME}_Lib2 INTERFACE
  $<BUILD_INTERFACE:${ABSOLUTE_PUBLIC_HEADERS}>
  $<INSTALL_INTERFACE:${PUBLIC_HEADERS}>
)
target_include_directories(${PROJECT_NAME}_Lib2 INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
set_target_properties(${PROJECT_NAME}_Lib2 PROPERTIES
  EXPORT_NAME Lib2
)

# Testing
if(BUILD_TESTING OR ${PROJECT_NAME}_BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}_Lib2 EXPORT ${PROJECT_NAME}Config)
install(FILES ${PUBLIC_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/lib2
)
