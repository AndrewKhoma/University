add_library(imgui
        include/imconfig.h include/imgui.h src/imgui.cpp
        include/imgui_impl_glfw.h src/imgui_impl_glfw.cpp
        include/imgui_impl_opengl3.h src/imgui_impl_opengl3.cpp
        src/imgui_draw.cpp
        include/imgui_internal.h
        src/imgui_widgets.cpp)

target_include_directories(imgui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(imgui PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)
