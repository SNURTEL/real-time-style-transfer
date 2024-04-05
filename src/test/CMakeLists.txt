find_package(Catch2 REQUIRED)

add_executable(tests test-sanity/test-sanity.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)


include(CTest)
include(Catch)
catch_discover_tests(tests)