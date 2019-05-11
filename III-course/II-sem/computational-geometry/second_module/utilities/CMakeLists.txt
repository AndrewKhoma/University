add_library(utils
        include/GLFWUtility.h src/GLFWUtility.cpp
        include/AlgorithmUtility.h src/AlgorithmUtility.cpp)

target_include_directories(utils PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(utils PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
