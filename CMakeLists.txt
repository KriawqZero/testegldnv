cmake_minimum_required(VERSION 3.30)
set(CMAKE_TOOLCHAIN_FILE C:/Users/Marcilio/Marcilio/PROJECTS/CPP/openglmoderno/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(testegldnv)

# Encontrar e incluir OpenGL
find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/source/include
                    ${CMAKE_SOURCE_DIR}/vendor/imgui
                    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends)

file(COPY ${CMAKE_SOURCE_DIR}/source/Shader/fragment_shader.frag DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/source/Shader/vertex_shader.vert DESTINATION ${CMAKE_BINARY_DIR})

set(IMGUI_FILES vendor/imgui/backends/imgui_impl_glfw.cpp
                vendor/imgui/backends/imgui_impl_glfw.h
                vendor/imgui/backends/imgui_impl_opengl2.cpp
                vendor/imgui/backends/imgui_impl_opengl2.h
                vendor/imgui/backends/imgui_impl_opengl3.cpp
                vendor/imgui/backends/imgui_impl_opengl3.h
                vendor/imgui/imgui.cpp
                vendor/imgui/imgui.h
                vendor/imgui/imgui_demo.cpp
                vendor/imgui/imgui_draw.cpp
                vendor/imgui/imgui_internal.h
                vendor/imgui/imgui_tables.cpp
                vendor/imgui/imgui_widgets.cpp)


set(SOURCE_FILES source/main.cpp
                source/Game/Game.cpp
                source/Game/Game.hpp

                source/Shader/Shader.cpp
                source/Shader/Shader.hpp
                source/Shader/shaderHelper.hpp

                source/World/Triangle/Triangle.cpp
                source/World/Triangle/Triangle.hpp

                source/Callbacks/Callback.cpp
                source/Callbacks/Callback.hpp

                source/Camera/Camera.cpp
                source/Camera/Camera.hpp

                source/WindowTool/WindowTool.cpp
                source/WindowTool/WindowTool.hpp
        source/World/Primitive/Primitive.cpp
        source/World/Primitive/Primitive.hpp
        source/World/Block/Block.cpp
        source/World/Block/Block.hpp
        source/World/Terrain/Terrain.cpp
        source/World/Terrain/Terrain.hpp)

add_executable(testegldnv ${SOURCE_FILES} ${IMGUI_FILES})
target_link_libraries(testegldnv PRIVATE OpenGL::GL glfw glm::glm GLEW::GLEW)
