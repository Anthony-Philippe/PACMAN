#ifndef FRUIT_H
#define FRUIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

enum FruitType{
    CHERRY,
    BANANA,
    APPLE,
    STRAWBERRY,
    ORANGE,
    WATERMELON,
};

class Fruit{
public:
    Fruit(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, FruitType type);
    ~Fruit();

    void render();

private:
    SDL_Texture* loadTexture(const std::string& path);
    FruitType type;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;

    int posX, posY;
};

#endif
