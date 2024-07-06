#ifndef GHOST_H
#define GHOST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <random>

class Ghost{
public:
    Ghost(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
    ~Ghost();

    void move();
    void updateDirection();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    int posX, posY;
    int velX, velY;

    int currentDirection;
    int changeDirectionTimer;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

#endif // GHOST_H
