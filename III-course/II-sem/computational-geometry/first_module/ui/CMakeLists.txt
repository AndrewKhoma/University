add_library(ui include/UI.h src/UI.cpp
        src/DrawableObject.h src/DrawableObject.cpp src/DrawableObserver.h src/DrawableObserver.cpp)

target_link_libraries(ui algo camera shader utils)

target_include_directories(ui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(ui PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
