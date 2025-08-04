cmake_minimum_required(VERSION 3.8)

project(tests)

enable_testing()
add_subdirectory(googletest)
add_executable(tests tests.cpp)
target_link_libraries(tests gtest_main gmock_main)