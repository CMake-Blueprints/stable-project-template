link_libraries(${PROJECT_NAME}_Lib2)

add_executable(${PROJECT_NAME}_Lib2Test ut.cpp)
add_test(NAME ${PROJECT_NAME}_Lib2Test COMMAND ${PROJECT_NAME}_Lib2Test)
