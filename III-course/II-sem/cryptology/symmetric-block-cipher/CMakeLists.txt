add_library(sym-block-cipher
        include/des.h src/des.cpp
        include/des_cbc.h src/des_cbc.cpp
        include/des_data.h include/des_key.h)

target_include_directories(sym-block-cipher PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(sym-block-cipher PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
