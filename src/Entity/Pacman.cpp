#include "Pacman.h"
#include <iostream>
#include <SDL2/SDL_image.h>

Pacman::Pacman(SDL_Renderer* renderer, const std::string& texturePath, int x, int y)
    : renderer(renderer), posX(x), posY(y), prevPosX(x), prevPosY(y), velX(0), velY(0), speed(5),
      direction(RIGHT), mouthOpen(true), frameCounter(0) {
    texture = loadTexture(texturePath);
    if (!texture) {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    srcRect = {0, 0, 32, 32};
    dstRect = {posX, posY, 32, 32};
}

Pacman::~Pacman(){
    SDL_DestroyTexture(texture);
}

SDL_Texture* Pacman::loadTexture(const std::string& path) {
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


void Pacman::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: velX = 0; velY = -speed; direction = UP; break;
        case SDLK_DOWN: velX = 0; velY = speed; direction = DOWN; break;
        case SDLK_LEFT: velX = -speed; velY = 0; direction = LEFT; break;
        case SDLK_RIGHT: velX = speed; velY = 0; direction = RIGHT; break;
        }
    }
}

void Pacman::move() {
    prevPosX = posX;
    prevPosY = posY;

    posX += velX;
    posY += velY;

    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX > 800 - dstRect.w) posX = 800 - dstRect.w;
    if (posY > 600 - dstRect.h) posY = 600 - dstRect.h;

    dstRect.x = posX;
    dstRect.y = posY;

    updateTexture();
}

void Pacman::render(){
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

void Pacman::setSpeed(int newSpeed) {
    speed = newSpeed;

    if (velX > 0) velX = speed;
    else if (velX < 0) velX = -speed;
    if (velY > 0) velY = speed;
    else if (velY < 0) velY = -speed;
}

void Pacman::updateTexture() {
    int rowOffset = mouthOpen ? 0 : 32;
    switch (direction) {
    case RIGHT: srcRect = {32, rowOffset, 32, 32}; break;
    case LEFT: srcRect = {0, rowOffset, 32, 32}; break;
    case UP: srcRect = {96, rowOffset, 32, 32}; break;
    case DOWN: srcRect = {64, rowOffset, 32, 32}; break;
    }

    if (posX != prevPosX || posY != prevPosY) {
        frameCounter++;
        if (frameCounter >= frameDelay) {
            mouthOpen = !mouthOpen;
            frameCounter = 0;
        }
    } else {
        frameCounter = 0;
    }
}