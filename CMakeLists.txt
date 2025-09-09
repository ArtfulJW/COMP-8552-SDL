cmake_minimum_required(VERSION 4.0)
project(COMP_8552_Week1_CLion)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(SDL3_PATH "C:/sdl3")
    set(SDL3_IMAGE_PATH "C:/sdl3_image")
    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
    )
    link_directories(
            ${SDL3_PATH}/lib
            ${SDL3_IMAGE_PATH}/lib
    )
endif()

add_executable(COMP_8552_Week1_CLion src/main.cpp src/Game.cpp
        src/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp)

target_link_libraries(COMP_8552_Week1_CLion
        SDL3
        SDL3_image
)