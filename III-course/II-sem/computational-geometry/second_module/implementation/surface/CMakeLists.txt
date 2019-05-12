add_library(ui_impl include/UIImpl.h src/UIImpl.cpp)

target_link_libraries(ui_impl algo ui)

target_include_directories(ui_impl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(ui_impl PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
