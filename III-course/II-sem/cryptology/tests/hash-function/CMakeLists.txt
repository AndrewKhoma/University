add_executable(md4-test md4-test.cpp)

target_link_libraries(md4-test
        gtest gtest_main pthread
        hash-func)

set_target_properties(md4-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)


gtest_add_tests(TARGET md4-test
        TEST_LIST md4-gtest)