add_library(number-theory
        include/number_theory.h src/number_theory.cpp
        include/montgomery_arithmetic.h src/montgomery_arithmetic.cpp)

target_link_libraries(number-theory PUBLIC gmp)

target_include_directories(number-theory PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(number-theory PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
