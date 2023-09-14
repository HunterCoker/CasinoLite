cmake_minimum_required(VERSION 3.25)
project(CasinoLite)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL" EXCLUDE_FROM_ALL)

set(CORE_SOURCES
        "Core/Application.cpp"
        "Core/Input.cpp"
        "Core/Game.hpp"
        "Core/Games/MainMenu.cpp"
        "Core/Games/Slots.cpp")

set(RENDERER_SOURCES
        "Renderer/Renderer.cpp")

add_executable(CasinoLite main.cpp  ${CORE_SOURCES} ${RENDERER_SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL/include")

target_link_libraries(${PROJECT_NAME}
        PRIVATE SDL3::SDL3)