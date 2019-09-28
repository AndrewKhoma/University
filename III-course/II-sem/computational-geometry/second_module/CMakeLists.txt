cmake_minimum_required(VERSION 3.13)
project(computational_geometry)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(LIBS ${GLFW3_LIBRARY} glfw GL ${OPENGL_LIBRARIES})

add_subdirectory(utilities)
add_subdirectory(imgui)
add_subdirectory(tinynurbs)
add_subdirectory(algorithm)
add_subdirectory(camera)
add_subdirectory(shader)

add_subdirectory(ui)

add_compile_definitions(-fPIC)

add_subdirectory(implementation/surface)

add_executable(comp-geom glad.c main.cpp)

target_link_libraries(comp-geom ui ui_impl)

configure_file(resources/shader.frag resources/shader.frag COPYONLY)
configure_file(resources/shader.vert resources/shader.vert COPYONLY)
configure_file(resources/shader3d.vert resources/shader3d.vert COPYONLY)

target_include_directories(comp-geom PUBLIC
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS})

target_compile_definitions(comp-geom PUBLIC
        ${OPENGL_DEFINITIONS})

target_link_libraries(comp-geom
        ${LIBS})

set_target_properties(comp-geom PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF)