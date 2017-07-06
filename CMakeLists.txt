cmake_minimum_required(VERSION 3.5)
project(eater_snek)

add_definitions(-std=c++11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(
        NAME eater_snek_tests
        COMMAND eater_snek_tests
)
