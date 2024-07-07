#ifndef GHOST_H
#define GHOST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <random>
#include <iostream>

enum GhostType{ BLINKY, PINKY, INKY, CLYDE };

class Ghost{
public:
    Ghost(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, GhostType type);
    ~Ghost();

    void render();
    void move();
    void setSpeed(int speed);

private:
    SDL_Texture* loadTexture(const std::string& path);
    GhostType type;
    void updateTexture();
    void changeDirection();

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;

    int posX, posY;
    int velX, velY;
    int speed;

    enum Direction{ RIGHT, LEFT, UP, DOWN } direction;

    std::mt19937 mt;
    std::uniform_int_distribution<int> directionDistribution;
};

#endif // GHOST_H
