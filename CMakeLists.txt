cmake_minimum_required(VERSION 3.15...3.27)

project(algae LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
