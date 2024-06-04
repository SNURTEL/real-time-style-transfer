# triggers false negatives
#find_package(Catch2 REQUIRED)

add_executable(tests 
    test_utils.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE common)


include(CTest)
include(Catch)
catch_discover_tests(tests)