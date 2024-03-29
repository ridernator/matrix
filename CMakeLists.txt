cmake_minimum_required(VERSION 3.10)

project(matrix VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)
set(INC_DIR include)

##################################################
# Main application                               #
##################################################
set(APPLICATION_NAME matrix)

add_executable(${APPLICATION_NAME} ${SRC_DIR}/Matrix.cc
                                   ${SRC_DIR}/Drop.cc)

target_include_directories(${APPLICATION_NAME} PUBLIC ${INC_DIR})

target_link_libraries(${APPLICATION_NAME} PUBLIC ncurses)

target_compile_options(${APPLICATION_NAME} PUBLIC -Wall
                                                  -Wextra
                                                  -pedantic
                                                  -Werror
                                                  -ggdb)
                                                  # -s -O3)
