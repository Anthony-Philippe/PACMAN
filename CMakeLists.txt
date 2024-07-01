cmake_minimum_required(VERSION 3.29)
project(PACMAN)

set(CMAKE_CXX_STANDARD 26)

# Chemins locaux pour SDL2 et SDL2_image
set(SDL2_LOCAL_DIR "$ENV{HOME}/libs/SDL2_local")
set(SDL2_IMAGE_LOCAL_DIR "$ENV{HOME}/libs/SDL2_image_local")

# Ajouter les chemins d'inclusion pour SDL2 et SDL2_image
include_directories(${SDL2_LOCAL_DIR}/include ${SDL2_IMAGE_LOCAL_DIR}/include)

# Ajouter les chemins des bibliothèques pour SDL2 et SDL2_image
link_directories(${SDL2_LOCAL_DIR}/lib ${SDL2_IMAGE_LOCAL_DIR}/lib)

# Recherchez et liez SDL2 et SDL2_image manuellement
find_library(SDL2_LIBRARY SDL2 HINTS ${SDL2_LOCAL_DIR}/lib)
find_library(SDL2_IMAGE_LIBRARY SDL2_image HINTS ${SDL2_IMAGE_LOCAL_DIR}/lib)

add_executable(PACMAN src/main.cpp src/Game/Game.cpp)
target_link_libraries(PACMAN ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
