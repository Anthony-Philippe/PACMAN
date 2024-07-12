#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Map {
public:
    Map(SDL_Renderer* renderer);
    ~Map();

    bool loadMap(const std::string& filePath);
    void render();

private:
    SDL_Renderer* renderer;
    std::vector<std::vector<int>> map;
    const int TILE_SIZE = 20;

    bool isWall(int tileID);
};

#endif