cmake_minimum_required(VERSION 3.29)
project(PACMAN)

set(CMAKE_CXX_STANDARD 26)

set(SDL2_LOCAL_DIR "$ENV{HOME}/libs/SDL2_local")
set(SDL2_IMAGE_LOCAL_DIR "$ENV{HOME}/libs/SDL2_image_local")
set(SDL2_TTF_LOCAL_DIR "$ENV{HOME}/libs/SDL2_ttf_local")

include_directories(${SDL2_LOCAL_DIR}/include ${SDL2_IMAGE_LOCAL_DIR}/include ${SDL2_TTF_LOCAL_DIR}/include)

link_directories(${SDL2_LOCAL_DIR}/lib ${SDL2_IMAGE_LOCAL_DIR}/lib ${SDL2_TTF_LOCAL_DIR}/lib)

find_library(SDL2_LIBRARY SDL2 HINTS ${SDL2_LOCAL_DIR}/lib)
find_library(SDL2_IMAGE_LIBRARY SDL2_image HINTS ${SDL2_IMAGE_LOCAL_DIR}/lib)
find_library(SDL2_TTF_LIBRARY SDL2_ttf HINTS ${SDL2_TTF_LOCAL_DIR}/lib)

add_executable(PACMAN src/main.cpp src/Game/Game.cpp src/Menu/Menu.cpp src/Menu/OptionsMenu.cpp src/Menu/GameRules.cpp)
target_link_libraries(PACMAN ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})