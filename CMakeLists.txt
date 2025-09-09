cmake_minimum_required(VERSION 4.0)
project(COMP_8552_Week1_CLion)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(SDL3_PATH "C:/sdl3")
    include_directories(${SDL3_PATH}/include)
    link_directories(${SDL3_PATH}/lib)
endif()

add_executable(COMP_8552_Week1_CLion main.cpp Game.cpp)

target_link_libraries(COMP_8552_Week1_CLion SDL3)