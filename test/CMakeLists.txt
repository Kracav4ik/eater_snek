set(gtest_disable_pthreads on) # needed in MinGW?
add_subdirectory(googletest-release-1.8.0)

find_package(Qt5Core REQUIRED)

add_executable(eater_snek_tests pathfinding_check.cpp)

target_link_libraries(eater_snek_tests gtest gtest_main eater_snek_common Qt5::Core)
