#include "Ghost.h"
#include <iostream>

Ghost::Ghost(SDL_Renderer* renderer, const std::string& texturePath, int x, int y)
    : renderer(renderer), posX(x), posY(y), velX(2), velY(2), currentDirection(0), changeDirectionTimer(0),
      gen(rd()), dis(0, 3){
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface){
        std::cerr << "Failed to load surface: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture){
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    srcRect = {0, 64, 32, 32};
    dstRect = {posX, posY, 32, 32};
}

Ghost::~Ghost(){
    SDL_DestroyTexture(texture);
}

void Ghost::move(){
    posX += velX;
    posY += velY;
    dstRect.x = posX;
    dstRect.y = posY;
}

void Ghost::updateDirection(){
    if (changeDirectionTimer <= 0){
        changeDirectionTimer = 128;

        int newDirection = dis(gen);
        while (newDirection == currentDirection){
            newDirection = dis(gen);
        }
        currentDirection = newDirection;

        switch (currentDirection){
        case 0:
            velX = 2;
            velY = 0;
            srcRect.y = 160;
            break;
        case 1:
            velX = -2;
            velY = 0;
            srcRect.y = 128;
            break;
        case 2:
            velX = 0;
            velY = -2;
            srcRect.y = 64;
            break;
        case 3:
            velX = 0;
            velY = 2;
            srcRect.y = 96;
            break;
        }
    }
    else{
        changeDirectionTimer--;
    }
}

void Ghost::render(){
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
