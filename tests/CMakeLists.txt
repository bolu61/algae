include(FetchContent)
include(CTest)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE unit_test_cases *.cxx)
add_executable(unit_test ${unit_test_cases})
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain algae)
add_test(NAME unit_test COMMAND unit_test)
