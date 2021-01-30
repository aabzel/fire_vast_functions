cmake_minimum_required(VERSION 3.19)

message("current dirrectory  ${CMAKE_CURRENT_SOURCE_DIR}")

set(PATH_SRC   ${CMAKE_CURRENT_SOURCE_DIR})
set(INCL_PATH_TESTS  ${PATH_SRC}/../tests)
set(INCL_PATH_UTILS  ${PATH_SRC}/../utils)

set(LIST_SRC fire_vast_functions.cpp 
             unit_test.cpp 
             ${INCL_PATH_UTILS}/utils_cpp.cpp)
set(OPT -Wall -fexceptions -g -Weffc++ -std=c++14 -DDEBUG_LIST_OF_ALL_FUNCTIONS -DGENERATE_HEADER -I${INCL_PATH_TESTS}  -I${INCL_PATH_UTILS})
set(CMAKE_GENERATOR "MinGW Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")
message("PATH_SRC=${PATH_SRC}")
message("LIST_SRC=${LIST_SRC}")
message("OPT=${OPT}")

set(PROJECT_NAME fire_vast_functions)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



