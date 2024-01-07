add_executable(${PROJECT_NAME}Test it.cpp)
target_link_libraries(${PROJECT_NAME}Test PRIVATE
  ${PROJECT_NAME}::Lib1
  ${PROJECT_NAME}::Lib2
)
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)
