cmake_minimum_required(VERSION 3.15...3.27)

project(algae LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

file(GLOB_RECURSE sources src/algae/*.hxx)
add_library(algae INTERFACE ${sources})
target_include_directories(algae INTERFACE $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

file(GLOB_RECURSE test_cases src/tests/algae/*.cxx)
add_executable(tests ${test_cases})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests)
