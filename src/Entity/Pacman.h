#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Pacman {
public:
    Pacman(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
    ~Pacman();

    void handleEvent(SDL_Event& e);
    void move();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    int posX, posY;
    int velX, velY;

    SDL_Texture* loadTexture(const std::string& path);
};

#endif