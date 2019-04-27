add_executable(des-test des-test.cpp)

target_link_libraries(des-test
        gtest gtest_main pthread
        sym-block-cipher)

set_target_properties(des-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)


gtest_add_tests(TARGET des-test
        TEST_LIST des-gtest)