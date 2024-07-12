#include "Map.h"

Map::Map(SDL_Renderer* renderer)
    : renderer(renderer) {
}

Map::~Map() {
}

bool Map::loadMap(const std::string& filePath) {
    std::ifstream file("map.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        int tile;
        while (ss >> tile) {
            row.push_back(tile);
        }
        map.push_back(row);
    }

    file.close();
    return true;
}

void Map::render() {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (isWall(map[y][x])) {
                SDL_Rect wallRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
                SDL_RenderFillRect(renderer, &wallRect);
            }
        }
    }
}

bool Map::isWall(int tileID) {
    return tileID == 26 || tileID == 30 || tileID == 27;
}