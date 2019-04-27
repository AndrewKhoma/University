# Binary power test
add_executable(bin-pow-test binary-power-test.cpp)

target_link_libraries(bin-pow-test
        gtest gtest_main pthread
        number-theory)

set_target_properties(bin-pow-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)

gtest_add_tests(TARGET bin-pow-test
        TEST_LIST bin-pow-gtest)

# Prime test
add_executable(prime-test prime-test.cpp)

target_link_libraries(prime-test
        gtest gtest_main pthread
        number-theory)

set_target_properties(prime-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)

gtest_add_tests(TARGET prime-test
        TEST_LIST prime-gtest)

# Karatsuba multiplication test
add_executable(karatsuba-test karatsuba-test.cpp)

target_link_libraries(karatsuba-test
        gtest gtest_main pthread
        number-theory)

set_target_properties(karatsuba-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)

gtest_add_tests(TARGET karatsuba-test
        TEST_LIST karatsuba-gtest)

# Extended Euclidean algorithm test
add_executable(extended-euclidean-test extended-euclidean-test.cpp)

target_link_libraries(extended-euclidean-test
        gtest gtest_main pthread
        number-theory)

set_target_properties(extended-euclidean-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)

gtest_add_tests(TARGET extended-euclidean-test
        TEST_LIST extended-euclidean-gtest)

# Montgomery arithmetic test
add_executable(montgomery-arithmetic-test montgomery-arithmetic-test.cpp)

target_link_libraries(montgomery-arithmetic-test
        gtest gtest_main pthread
        number-theory)

set_target_properties(montgomery-arithmetic-test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)

gtest_add_tests(TARGET montgomery-arithmetic-test
        TEST_LIST montgomery-arithmetic-gtest)

