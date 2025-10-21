cmake_minimum_required(VERSION 4.0)
project(COMP_8552_Week1_CLion)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(SDL3_PATH "C:/sdl3")
    set(SDL3_IMAGE_PATH "C:/sdl3_image")
    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/src/utils
            ${PROJECT_SOURCE_DIR}/src/ecs
            ${PROJECT_SOURCE_DIR}/src/ecs/system
            ${PROJECT_SOURCE_DIR}/src/vendor
    )
    link_directories(
            ${SDL3_PATH}/lib
            ${SDL3_IMAGE_PATH}/lib
    )
endif()

add_executable(COMP_8552_Week1_CLion src/main.cpp src/Game.cpp
        src/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp
        src/ecs/ComponentType.h
        src/ecs/Entity.h
        src/ecs/Component.h
        src/ecs/system/MovementSystem.cpp
        src/ecs/system/MovementSystem.h
        src/ecs/system/RenderSystem.h
        src/ecs/World.h
        src/utils/Vector2D.cpp
        src/utils/Collision.h
        src/utils/Collision.cpp
        src/ecs/system/CollisionSystem.h
        src/ecs/system/CollisionSystem.cpp
        src/ecs/World.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/manager/Scene.cpp
)

target_link_libraries(COMP_8552_Week1_CLion
        SDL3
        SDL3_image
)