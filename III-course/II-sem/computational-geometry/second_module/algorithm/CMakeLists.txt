add_library(algo include/Algorithm.h src/Algorithm.cpp)

target_link_libraries(algo tinynurbs utils)

target_include_directories(algo PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

target_compile_features(algo PRIVATE cxx_std_14)

set_target_properties(algo PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
