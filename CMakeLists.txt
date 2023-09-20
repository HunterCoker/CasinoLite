cmake_minimum_required(VERSION 3.25)
project(CasinoLite)

set(CMAKE_CXX_STANDARD 17)

set(CORE_SOURCES
    "Core/Application.cpp"
    "Core/Input.cpp"
    "Core/Game.hpp"
    "Core/Games/MainMenu.cpp"
    "Core/Games/Slots.cpp")

set(RENDERER_SOURCES
    "Renderer/Shader.cpp"
    "Renderer/Texture.cpp"
    "Renderer/Camera.cpp"
    "Renderer/Primitive.cpp"
    "Renderer/Renderer.cpp"
    "Renderer/VertexArray.cpp"
    "Renderer/Buffers.cpp")

set(OTHER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/stb.cpp")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw")
add_executable(CasinoLite main.cpp ${CORE_SOURCES} ${RENDERER_SOURCES} ${OTHER_SOURCES} )

target_include_directories(${PROJECT_NAME}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")

target_link_libraries(${PROJECT_NAME}
        PRIVATE glfw)