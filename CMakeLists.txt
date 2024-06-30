cmake_minimum_required(VERSION 3.29)
project(PACMAN)

set(CMAKE_CXX_STANDARD 26)

execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/install_sdl.sh)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(PACMAN src/main.cpp)
target_link_libraries(PACMAN ${SDL2_LIBRARIES})
