cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread -fprofile-arcs -ftest-coverage")

set(CMAKE_C_FLAGS_PROFILE --coverage)
set(CMAKE_CXX_FLAGS_PROFILE --coverage)




SET(MYCOMPILE_FLAGS "-Wall -Werror -Wpedantic")
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${MYCOMPILE_FLAGS}")

add_compile_options("-lgcov --coverage")


add_executable(main main.c)

#target_link_libraries(main gcov)

set(LIB_SOURCE_FILES_GENERAL general_functions.c)
add_library(general_functions STATIC ${LIB_SOURCE_FILES_GENERAL})
target_link_libraries(main general_functions)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(general_functions_test general_functions_test.cpp)
target_link_libraries(general_functions_test ${GTEST_LIBRARIES} general_functions)



if( STATIC ) 
    message("STATIC")
    set(LIB_SOURCE_FILES_STATIC static.c)
    add_library(static STATIC ${LIB_SOURCE_FILES_STATIC})
    target_link_libraries(main static)

    
    add_executable(static_test static_test.cpp)
    target_link_libraries(static_test ${GTEST_LIBRARIES} static)
    target_link_libraries(static_test ${GTEST_LIBRARIES} general_functions)
else()
    message("DYNAMIC")
    set(LIB_SOURCE_FILES_DYNAMIC dynamic.c)
    add_library(dynamic SHARED ${LIB_SOURCE_FILES_DYNAMIC})
    target_link_libraries(main dynamic)


    
    add_executable(dynamic_test dynamic_test.cpp)
    target_link_libraries(dynamic_test ${GTEST_LIBRARIES} dynamic)
    target_link_libraries(dynamic_test ${GTEST_LIBRARIES} general_functions)
endif()


#target_link_libraries(main gcov)



