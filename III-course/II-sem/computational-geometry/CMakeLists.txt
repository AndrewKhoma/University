cmake_minimum_required(VERSION 3.13)
project(computational_geometry)

find_package(glm REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(X11 REQUIRED)

set(LIBS ${GLFW3_LIBRARY} glfw X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${ASSIMP_LIBRARY})

add_executable(comp-geom glad.c main.cpp shader/Shader.cpp shader/Shader.h camera/Camera.cpp camera/Camera.h ui/UI.cpp ui/UI.h)

configure_file(resources/shader.frag resources/shader.frag COPYONLY)
configure_file(resources/shader.vert resources/shader.vert COPYONLY)

target_include_directories(comp-geom PUBLIC
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS})

target_compile_definitions(comp-geom PUBLIC
        ${OPENGL_DEFINITIONS})

target_link_libraries(comp-geom
        ${LIBS}
        ${OPENGL_LIBRARIES})

set_target_properties(comp-geom PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)