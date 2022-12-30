cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_FLAGS "-Werror -Wextra -Wall -g")

add_executable(test main.cpp tester.cpp tester_vector.cpp tester_map.cpp tester_stack.cpp tester_set.cpp)
