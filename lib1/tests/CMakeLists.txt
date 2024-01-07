include_directories($<TARGET_PROPERTY:${PROJECT_NAME}_Lib1,INCLUDE_DIRECTORIES>)
add_definitions(-DMyProject_Lib1_EXPORTS)

add_executable(${PROJECT_NAME}_Lib1Test ut.cpp ../src/lib1.cpp)
add_test(NAME ${PROJECT_NAME}_Lib1Test COMMAND ${PROJECT_NAME}_Lib1Test)
