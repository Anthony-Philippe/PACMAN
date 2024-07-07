#include "Fruit.h"

Fruit::Fruit(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, FruitType type)
    : renderer(renderer), posX(x), posY(y), type(type) {
    texture = loadTexture(texturePath);
    if (!texture) {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    int column = type % 3;
    int row = type / 3;

    srcRect = {(column * 32) + 256, (row * 32) + 128, 32, 32};
    dstRect = {posX, posY, 32, 32};
}

Fruit::~Fruit() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Fruit::loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Fruit::render() {
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}